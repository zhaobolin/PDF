template<typename T> string toString(const T& t){
    ostringstream oss;  //����һ����ʽ�������
    oss<<t;             //��ֵ����������
    return oss.str();  
}