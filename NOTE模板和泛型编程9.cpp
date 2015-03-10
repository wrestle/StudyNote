模板和泛型编程
//模板函数和函数重载能实现相同的目的,但是会导致涵义模糊.
01.   template <class T>//class和typename 两个关键字都行,相同的效果
                        //<>中间称为模板参数,不能为空
      int compate(const T &v1, const T &v2)
      {
        if(v1 < v2) return -1;
        if(v2 < v1) return  1;
        return 0;
      }
      当我们使用这个函数模板的时候,我们使用模板实参(不管隐式还是显式)去绑定模板形参.
      当我们使用这个函数模板的时候,编译器通过函数的参数判断'T'该是什么类型.
      当我们使用这个函数模板的时候,编译器生成一个明确的函数参数代码来替代原有的函数模板参数
         即 int compare(const T &v1, const T &v2); 换成
            int compare(const int &v1, const int &v2);//假设调用compare(1,1);
      
