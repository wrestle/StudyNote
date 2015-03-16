模板和泛型编程
//模板函数和函数重载能实现相同的目的,但是会导致涵义模糊.
//模板只有在我们调用了它之后才会生成相应代码,否则即使定义了它也不会生效占地方.
//模板函数能够被inline 和 constexpr 关键字修饰,但必须在模板参数('>')之后
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
02.   无类型的模板形参(Nontype Template Parameters)
       此种用法的模板参数必须是常量表达式(constant expression).
       能够由编译器或者所传递的参数,自动推断出对应的无类型参数的值:
         template<unsigned N, unsigned M>
         int compare(const char (&p1)[N], const char (&p2)[M]){...}
         compare("hi", "mom");//调用,则实际上是生成了
                              //int compare(const char (&p1)[3],
                              //            const char (&p2)[4]){...}
                              //因为我们无法将整个数组进行拷贝传递,所以我们使用引用的手法进行传递.
03.   模板函数的定义以及声明最好遵守以下法则:
        函数的参数是(常量引用),以此来避免复制实参,带来不必要的开销.
        在进行运算时,运算符应该相对的尽可能减少(例如'<'和'>'我们只需要实现'<'即可);
04.   模板的生成规则 Page-656:
        普通函数,当我们在调用它的时候,编译器并不需要知道函数的定义,只需要找到函数的声明即可,当我们
       调用一个对象的时候,我们需要看到这个对象的类定义,但类的成员函数的定义则不需要看见,只需要看到
       他们的声明即可.
        模板函数或者模板成员函数则不同,编译器需要知道他们的定义才能生成相应的代码,所以模板函数的定义
       通常放在头文件中.
05.   类模板(Class Template)
       1 类模板生成的任一个类都是独立的,无不干扰的.
       2 我们常常使用一个模板的参数来作为另一个模板的参数,在同一作用域内,这是可行的.(shared_ptr<vector<T>>)
       3 和普通类一样,模板类的成员函数,同样可以选择在类内定义(隐式内联),或者类外定义.
       4 不同的是,我们在类外定义成员函数时候,需要加上模板参数.原因是我们可能会用这个模板生成很多类,
      但是成员函数可能是相同的,所以我们必须加上模板参数(template<typename T>)来标识函数定义:
      template<typename T>
      return_type class1<T>::member_function(para-list){}//pare-list 即为函数参数
      并且在使用类外成员函数的定义时,在函数体中也要带有模板参数(必要的时候)
       5 另外,只有当我们使用了模板类的某个成员函数时,它才会生成相应的函数代码,否则不会生成.
       6 在模板类中,我们可以省略模板参数:
      class1& menber_function(para-list);//此时的返回值class1并没有带上模板参数,但相当于
      class1<T>& menber_function(para-list);
06.   类模板与友元(Class Template and Friends)
      
