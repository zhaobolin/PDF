#include "fitz-internal.h"
#define debug
/*


void addroute(struct zblrouteset* getline)//为routeset添加一个route
{
	//初始化一个route
	struct zblroute* route=(struct zblroute*)malloc(sizeof(struct zblroute));
	//route=(zblroute*)malloc(sizeof(struct zblroute));
	route->countpoint=0;
	route->colorspace=-1;
	route->color[0]=-1;
	route->color[1]=-1;
	route->color[2]=-1;
	route->color[3]=-1;
	route->linewidth=-1;
	route->drawingmethord=-1;
	route->points=(struct routepoint*)malloc(sizeof(struct routepoint));
	route->currentpoint=route->points;
	route->currentpoint->nextpoint=NULL;
	addpoints(route);//添加一个空的点集
	route->existcm=0;
	route->matrix=NULL;
	route->type=0;
	route->next=NULL;//下一个route为空
	getline->current->next=route;
	getline->current=getline->current->next;
}
*/
void
fz_free_context(fz_context *ctx)
{
	if (!ctx)
		return;

	/* Other finalisation calls go here (in reverse order) */
	fz_drop_glyph_cache_context(ctx);
	fz_drop_store_context(ctx);
	fz_free_aa_context(ctx);
	fz_drop_font_context(ctx);

	if (ctx->warn)
	{
		fz_flush_warnings(ctx);
		fz_free(ctx, ctx->warn);
	}

	if (ctx->error)
	{
		assert(ctx->error->top == -1);
		fz_free(ctx, ctx->error);
	}

	/* Free the context itself */
	ctx->alloc->free(ctx->alloc->user, ctx);
}

/* Allocate new context structure, and initialise allocator, and sections
 * that aren't shared between contexts.
 */
static fz_context *
new_context_phase1(fz_alloc_context *alloc, fz_locks_context *locks)
{
	fz_context *ctx;

	ctx = alloc->malloc(alloc->user, sizeof(fz_context));
	if (!ctx)
		return NULL;
	memset(ctx, 0, sizeof *ctx);
	ctx->alloc = alloc;
	ctx->locks = locks;

	ctx->glyph_cache = NULL;

	ctx->error = fz_malloc_no_throw(ctx, sizeof(fz_error_context));
	if (!ctx->error)
		goto cleanup;
	ctx->error->top = -1;
	ctx->error->message[0] = 0;

	ctx->warn = fz_malloc_no_throw(ctx, sizeof(fz_warn_context));
	if (!ctx->warn)
		goto cleanup;
	ctx->warn->message[0] = 0;
	ctx->warn->count = 0;

	/* New initialisation calls for context entries go here */
	fz_try(ctx)
	{
		fz_new_aa_context(ctx);
	}
	fz_catch(ctx)
	{
		goto cleanup;
	}

	return ctx;

cleanup:
	fprintf(stderr, "cannot create context (phase 1)\n");
	fz_free_context(ctx);
	return NULL;
}

fz_context *
fz_new_context(fz_alloc_context *alloc, fz_locks_context *locks, unsigned int max_store)
{
	fz_context *ctx;

	if (!alloc)
		alloc = &fz_alloc_default;

	if (!locks)
		locks = &fz_locks_default;

	ctx = new_context_phase1(alloc, locks);

	/* Now initialise sections that are shared */
	fz_try(ctx)
	{
		fz_new_store_context(ctx, max_store);
		fz_new_glyph_cache_context(ctx);
		fz_new_font_context(ctx);
	}
	fz_catch(ctx)
	{
		fprintf(stderr, "cannot create context (phase 2)\n");
		fz_free_context(ctx);
		return NULL;
	}
	return ctx;
}

fz_context *
fz_clone_context(fz_context *ctx)
{
	/* We cannot safely clone the context without having locking/
	 * unlocking functions. */
	if (ctx == NULL || ctx->locks == &fz_locks_default)
		return NULL;
	return fz_clone_context_internal(ctx);
}

fz_context *
fz_clone_context_internal(fz_context *ctx)
{
	fz_context *new_ctx;

	if (ctx == NULL || ctx->alloc == NULL)
		return NULL;
	new_ctx = new_context_phase1(ctx->alloc, ctx->locks);
	/* Inherit AA defaults from old context. */
	fz_copy_aa_context(new_ctx, ctx);
	new_ctx->store = fz_keep_store_context(ctx);
	new_ctx->glyph_cache = fz_keep_glyph_cache(ctx);
	new_ctx->font = fz_keep_font_context(ctx);
	return new_ctx;
}

void addroute(struct zblstack* stack);
void addpoint(struct zblroute* route);
void addclippoint(struct zblstack* stack);

void addneststack(struct zblstack* pointer);
void recursion(struct zblstack* s,struct zblstack* d)//递归函数,用于递归的复制 ps:只读取一个树的内容
{
	//struct zblstack* spointer;//可能传入下一级的指针
	//struct zblstack* dpointer;
	int i;
	d->existstack=s->existstack;
	d->countroute=s->countroute;
	d->countclip=s->countclip;
	d->existclip=s->existclip;
	d->existnest=s->existnest;
	d->shadowtype=s->shadowtype;
	d->ca=s->ca;
	if(d->shadowtype!=0)
	{
		d->bcolor=(float*)malloc(4*sizeof(float));
		d->ecolor=(float*)malloc(4*sizeof(float));
		for(i=0;i<3;i++)
		{
			d->bcolor[i]=s->bcolor[i];
			d->ecolor[i]=s->ecolor[i];
		}
	}	

	if(s->existclip>0)//复制裁剪路径
		{
			s->currentclip=s->clipheadler;
			d->clipheadler=(struct routepoint*)malloc(sizeof(struct routepoint));
			d->currentclip=d->clipheadler;
			d->currentclip->nextpoint=NULL;
			while(s->currentclip->nextpoint!=NULL)
			{
				s->currentclip=s->currentclip->nextpoint;
				addclippoint(d);
				d->currentclip->p0=s->currentclip->p0;
				d->currentclip->p1=s->currentclip->p1;
				d->currentclip->p2=s->currentclip->p2;
				d->currentclip->p3=s->currentclip->p3;
				d->currentclip->p4=s->currentclip->p4;
				d->currentclip->p5=s->currentclip->p5;
				d->currentclip->state=s->currentclip->state;
			}
		}

		d->existcm=s->existcm;//复制转置矩阵
		if(d->existcm==1)
		{
			d->matrix=(float*)malloc(6*sizeof(float));
			d->matrix[0]=s->matrix[0];
			d->matrix[1]=s->matrix[1];
			d->matrix[2]=s->matrix[2];
			d->matrix[3]=s->matrix[3];
			d->matrix[4]=s->matrix[4];
			d->matrix[5]=s->matrix[5];
			//printf("转置矩阵 %f %f %f %f %f %f\n",d->matrix[0],d->matrix[1],d->matrix[2],d->matrix[3],d->matrix[4],d->matrix[5]);
		}

		s->currentroute=s->routeheadler;//s指向route链表的头结点
		while(s->currentroute->nextroute!=NULL)//遍历栈中路径
		{
			s->currentroute=s->currentroute->nextroute;
			d->currentroute->type=s->currentroute->type;
			//printf("\n route测试:路径类型%d\n",s->currentroute->type);
			d->currentroute->linewidth=s->currentroute->linewidth;
			//printf("\n route测试:线宽%f\n",s->currentroute->linewidth);
			d->currentroute->colorspace=s->currentroute->colorspace;
			d->currentroute->scolorspace=s->currentroute->scolorspace;
			if((d->currentroute->colorspace==3)||(d->currentroute->colorspace==4)||(d->currentroute->colorspace==5)||(d->currentroute->colorspace==6))//RGB 颜色空间
			{
				d->currentroute->color[0]=s->currentroute->color[0];
				d->currentroute->color[1]=s->currentroute->color[1];
				d->currentroute->color[2]=s->currentroute->color[2];
				d->currentroute->color[3]=s->currentroute->color[3];
				//printf("第一种颜色 %f %f %f\n",s->currentroute->color[0],s->currentroute->color[1],s->currentroute->color[2]);
			}
			else //灰度空间
			{
				d->currentroute->color[0]=s->currentroute->color[0];
			}
			//printf("scolorspace:%d\n",d->currentroute->scolorspace);
			if(d->currentroute->scolorspace!=0)//处理既填充又描边的操作,两组颜色
			{
				d->currentroute->scolorspace=s->currentroute->scolorspace;
				d->currentroute->scolor=(float*)malloc(4*sizeof(float));
				if((d->currentroute->scolorspace==3)||(d->currentroute->scolorspace==4)||(d->currentroute->scolorspace==5)||(d->currentroute->scolorspace==6))
				{
					d->currentroute->scolor[0]=s->currentroute->scolor[0];
					d->currentroute->scolor[1]=s->currentroute->scolor[1];
					d->currentroute->scolor[2]=s->currentroute->scolor[2];
					d->currentroute->scolor[3]=s->currentroute->scolor[3];
					//printf("\n特殊的第二种描边的颜色 %f %f %f\n\n",s->currentroute->scolor[0],s->currentroute->scolor[1],s->currentroute->scolor[2]);
				}
				else
				{
					d->currentroute->scolor[0]=s->currentroute->scolor[0];
				}
			}
			d->currentroute->drawingmethord=s->currentroute->drawingmethord;
			d->currentroute->countpoint=s->currentroute->countpoint;
			s->currentroute->currentpoint=s->currentroute->pointheadler;
			while(s->currentroute->currentpoint->nextpoint!=NULL)//遍历路径点
			{
				s->currentroute->currentpoint=s->currentroute->currentpoint->nextpoint;
				
				d->currentroute->currentpoint->p0=s->currentroute->currentpoint->p0;
				d->currentroute->currentpoint->p1=s->currentroute->currentpoint->p1;
				d->currentroute->currentpoint->p2=s->currentroute->currentpoint->p2;
				d->currentroute->currentpoint->p3=s->currentroute->currentpoint->p3;
				d->currentroute->currentpoint->p4=s->currentroute->currentpoint->p4;
				d->currentroute->currentpoint->p5=s->currentroute->currentpoint->p5;
				d->currentroute->currentpoint->state=s->currentroute->currentpoint->state;
				//printf("复制阶段路径点参数:%f %f %f %f %f %f %f \n",d->currentroute->currentpoint->p0,d->currentroute->currentpoint->p1,d->currentroute->currentpoint->p2,d->currentroute->currentpoint->p3,d->currentroute->currentpoint->p4,d->currentroute->currentpoint->p5,d->currentroute->currentpoint->state);
				if(d->currentroute->currentpoint->state!=-1)
				{
					addpoint(d->currentroute);
				}
			}
			if(d->currentroute->colorspace!=-1||d->currentroute->linewidth!=-1)
			{
				addroute(d);
			}
		}
		if(s->existnest==0)//若不存在嵌套栈内容,跳出
		{
			return ;
		}
		else//存在嵌套栈
		{
			s->currentstack=s->stackheadler;	
			while(s->currentstack->nextstack!=NULL)
			{
				//spointer=spointer->nextstack;
				s->currentstack=s->currentstack->nextstack;
				addneststack(d);
				recursion(s->currentstack,d->currentstack);
			}
		}
		return;
}



void initrouteset(struct zblrouteset* getline);
void addstack(struct zblrouteset* getline);
//void addroute(struct zblstack* stack);
//void addpoint(struct zblroute* route);
//void addclippoint(struct zblstack* stack);

extern struct zblrouteset * getline;
void fz_return_line(struct zblrouteset *p)//与我的工程的接口,取得PDF图形内容
{
	struct zblstack* spointer=NULL;//指针
	struct zblstack* dpointer=NULL;
	initrouteset(p);
	p->count=getline->count;
	getline->currentstack=getline->stackheadler;
	while(getline->currentstack->nextstack!=NULL)//第一层遍历栈,每次处理一棵树
	{
		getline->currentstack=getline->currentstack->nextstack;
		addstack(p);
		recursion(getline->currentstack,p->currentstack);
	}
	//printf("%d ",p->count);
}

/*
while(getline->currentstack->nextstack!=NULL)//遍历栈
	{
		getline->currentstack=getline->currentstack->nextstack;
		addstack(p);
		p->currentstack->existstack=getline->currentstack->existstack;
		p->currentstack->countroute=getline->currentstack->countroute;
		p->currentstack->countclip=getline->currentstack->countclip;
		p->currentstack->existclip=getline->currentstack->existclip;
		if(p->currentstack->existclip>0)//复制裁剪路径
		{
			getline->currentstack->currentclip=getline->currentstack->clipheadler;
			p->currentstack->clipheadler=(struct routepoint*)malloc(sizeof(struct routepoint));
			p->currentstack->currentclip=p->currentstack->clipheadler;
			p->currentstack->currentclip->nextpoint=NULL;
			while(getline->currentstack->currentclip->nextpoint!=NULL)
			{
				getline->currentstack->currentclip=getline->currentstack->currentclip->nextpoint;
				addclippoint(p->currentstack);
				p->currentstack->currentclip->p0=getline->currentstack->currentclip->p0;
				p->currentstack->currentclip->p1=getline->currentstack->currentclip->p1;
				p->currentstack->currentclip->p2=getline->currentstack->currentclip->p2;
				p->currentstack->currentclip->p3=getline->currentstack->currentclip->p3;
				p->currentstack->currentclip->p4=getline->currentstack->currentclip->p4;
				p->currentstack->currentclip->p5=getline->currentstack->currentclip->p5;
				p->currentstack->currentclip->state=getline->currentstack->currentclip->state;
			}
		}
		p->currentstack->existcm=getline->currentstack->existcm;
		if(p->currentstack->existcm==1)//复制转置矩阵
		{
			p->currentstack->matrix=(float*)malloc(6*sizeof(float));
			p->currentstack->matrix[0]=getline->currentstack->matrix[0];
			p->currentstack->matrix[1]=getline->currentstack->matrix[1];
			p->currentstack->matrix[2]=getline->currentstack->matrix[2];
			p->currentstack->matrix[3]=getline->currentstack->matrix[3];
			p->currentstack->matrix[4]=getline->currentstack->matrix[4];
			p->currentstack->matrix[5]=getline->currentstack->matrix[5];
		}
		getline->currentstack->currentroute=getline->currentstack->routeheadler;
		while(getline->currentstack->currentroute->nextroute!=NULL)//遍历栈中路径
		{
			getline->currentstack->currentroute=getline->currentstack->currentroute->nextroute;
			p->currentstack->currentroute->type=getline->currentstack->currentroute->type;
			printf("\n route测试:%d\n",getline->currentstack->currentroute->type);
			p->currentstack->currentroute->linewidth=getline->currentstack->currentroute->linewidth;
			printf("\n route测试:线宽%f\n",getline->currentstack->currentroute->linewidth);
			p->currentstack->currentroute->colorspace=getline->currentstack->currentroute->colorspace;
			if((p->currentstack->currentroute->colorspace==3)||(p->currentstack->currentroute->colorspace==4))//RGB 颜色空间
			{
				p->currentstack->currentroute->color[0]=getline->currentstack->currentroute->color[0];
				p->currentstack->currentroute->color[1]=getline->currentstack->currentroute->color[1];
				p->currentstack->currentroute->color[2]=getline->currentstack->currentroute->color[2];
				p->currentstack->currentroute->color[3]=getline->currentstack->currentroute->color[3];
			}
			else //灰度空间
			{
				p->currentstack->currentroute->color[0]=getline->currentstack->currentroute->color[0];
			}
			p->currentstack->currentroute->drawingmethord=getline->currentstack->currentroute->drawingmethord;
			p->currentstack->currentroute->countpoint=getline->currentstack->currentroute->countpoint;
			getline->currentstack->currentroute->currentpoint=getline->currentstack->currentroute->pointheadler;
			while(getline->currentstack->currentroute->currentpoint->nextpoint!=NULL)//遍历路径点
			{
				getline->currentstack->currentroute->currentpoint=getline->currentstack->currentroute->currentpoint->nextpoint;
				
				p->currentstack->currentroute->currentpoint->p0=getline->currentstack->currentroute->currentpoint->p0;
				p->currentstack->currentroute->currentpoint->p1=getline->currentstack->currentroute->currentpoint->p1;
				p->currentstack->currentroute->currentpoint->p2=getline->currentstack->currentroute->currentpoint->p2;
				p->currentstack->currentroute->currentpoint->p3=getline->currentstack->currentroute->currentpoint->p3;
				p->currentstack->currentroute->currentpoint->p4=getline->currentstack->currentroute->currentpoint->p4;
				p->currentstack->currentroute->currentpoint->p5=getline->currentstack->currentroute->currentpoint->p5;
				p->currentstack->currentroute->currentpoint->state=getline->currentstack->currentroute->currentpoint->state;
				printf("复制时的路径点%f %f\n",getline->currentstack->currentroute->currentpoint->p0,getline->currentstack->currentroute->currentpoint->p1);
				addpoint(p->currentstack->currentroute);
			}
			addroute(p->currentstack);
		}
	}
*/




//delete getline;
	/*int i=0,c,first;
	p->count=getline->count;
	p->headler=(struct zblroute*)malloc(sizeof(struct zblroute));
	p->current=p->headler;
	//p->headler=getline->headler;
	//p->current=p->headler;
	getline->current=getline->headler;
	while(getline->current->next!=NULL)//遍历route
	{
		first=0;
		getline->current=getline->current->next;
		addroute(p);
		//p->current=p->current->next;
		p->current->countpoint=getline->current->countpoint;
		p->current->colorspace=getline->current->colorspace;
		p->current->color[0]=getline->current->color[0];
		p->current->color[1]=getline->current->color[1];
		p->current->color[2]=getline->current->color[2];
		p->current->color[3]=getline->current->color[3];
		p->current->linewidth=getline->current->linewidth;
		p->current->drawingmethord=getline->current->drawingmethord;
		p->current->type=getline->current->type;
		p->current->existclip=getline->current->existclip;
		p->current->countclip=getline->current->countclip;
		p->current->clipregion=(struct routepoint*)malloc(sizeof(struct routepoint));
		p->current->currentclippoint=p->current->clipregion;
		if(getline->current->existcm==1)
		{
			p->current->matrix=(float*)malloc(6);
			p->current->existcm=1;
			for (c=0;c<6;c++)
			{
				p->current->matrix[c]=getline->current->matrix[c];
				printf("接口函数转置矩阵%f\n",getline->current->matrix[c]);
			}
		}
		else
		{
			p->current->existcm=0;
		}
		if(getline->current->existclip!=0)//若存在裁剪路径
		{
			while(i<getline->current->countclip)
			{
				if(first==0)
				{
					first++;
					getline->current->currentclippoint=getline->current->clipregion;
					printf("mupdf库层：：裁剪路径起点\n");
				}
				else
				{
					getline->current->currentclippoint=getline->current->currentclippoint->nextpoint;
					addclippoints(p->current);
				}
				//p->current->currentpoint=p->current->currentpoint->nextpoint;
				printf("mupdf库层裁剪路径::%f %f\n",getline->current->currentclippoint->p0,getline->current->currentclippoint->p1);
				p->current->currentclippoint->p0=getline->current->currentclippoint->p0;
				p->current->currentclippoint->p1=getline->current->currentclippoint->p1;
				p->current->currentclippoint->p2=getline->current->currentclippoint->p2;
				p->current->currentclippoint->p3=getline->current->currentclippoint->p3;
				p->current->currentclippoint->p4=getline->current->currentclippoint->p4;
				p->current->currentclippoint->p5=getline->current->currentclippoint->p5;
				p->current->currentclippoint->state=getline->current->currentclippoint->state;
				//addpoints(p->current);
				i++;
				}
		}
		else//不存在裁剪路径
		{
			p->current->clipregion=NULL;
			p->current->currentclippoint=NULL;
		}
		i=0;
		first=0;
		//getline->current->currentpoint=getline->current->points;
		while(i<getline->current->countpoint)//遍历points链表
		{
			if(first==0)
			{
				first++;
				getline->current->currentpoint=getline->current->points;
				printf("mupdf库层：：起点\n");
			}
			else
			{
				getline->current->currentpoint=getline->current->currentpoint->nextpoint;
				addpoints(p->current);
			}
			//p->current->currentpoint=p->current->currentpoint->nextpoint;
			printf("mupdf库层::%f %f\n",getline->current->currentpoint->p0,getline->current->currentpoint->p1);
			p->current->currentpoint->p0=getline->current->currentpoint->p0;
			p->current->currentpoint->p1=getline->current->currentpoint->p1;
			p->current->currentpoint->p2=getline->current->currentpoint->p2;
			p->current->currentpoint->p3=getline->current->currentpoint->p3;
			p->current->currentpoint->p4=getline->current->currentpoint->p4;
			p->current->currentpoint->p5=getline->current->currentpoint->p5;
			p->current->currentpoint->state=getline->current->currentpoint->state;
			//addpoints(p->current);
			i++;
		}
		i=0;
	}*/

	/*
	int i=0,j=0,c=0;
	p->count=getline->count;//路径数量
	printf("全局变量指针占用空间 %d\n",sizeof(getline));
	for (;i<getline->count;i++)
	{
		p->set[i].type=getline->set[i].type;//设置类型
		p->set[i].linewidth=getline->set[i].linewidth;//设置线宽
		p->set[i].colorspace=getline->set[i].colorspace;//设置色彩空间
		p->set[i].drawingmethord=getline->set[i].drawingmethord;//设置绘制方法类型
		if(getline->set[i].existcm==1)//若路径存在转置矩阵则提取
		{
			//printf("接口函数提取转置矩阵\n");
			p->set[i].existcm=1;
			p->set[i].matrix=(float*)malloc(6);
			for (c=0;c<6;c++)
			{
				p->set[i].matrix[c]=getline->set[i].matrix[c];
				//printf("%d %f\n",c,p->set[i].matrix[c]);
			}
		}
		else
		{
			p->set[i].existcm=0;
		}
		for(c=0;c<4;c++)
		{
			p->set[i].color[c]=getline->set[i].color[c];
		}
		p->set[i].countpoint=getline->set[i].countpoint;//每条路径的点数
		//p->set[i].drawingmethord=getline.set[i].drawingmethord;
		for (j=0;j<getline->set[i].countpoint;j++)
		{
			//printf("%d赋值函数:%f\n",i,jgetline.set[i].points[j][0]);
			p->set[i].points[j][0]=getline->set[i].points[j][0];
			p->set[i].points[j][1]=getline->set[i].points[j][1];
			p->set[i].points[j][2]=getline->set[i].points[j][2];
			p->set[i].points[j][3]=getline->set[i].points[j][3];
			p->set[i].points[j][4]=getline->set[i].points[j][4];
			p->set[i].points[j][5]=getline->set[i].points[j][5];
			p->set[i].points[j][6]=getline->set[i].points[j][6];
		}
		
	}
	*/