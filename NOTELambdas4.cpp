00. Lambdas Expression
    (1) 泛型算法能够使用任何可调用的对象(callable object)或者表达式,比如函数,或者或者函数指针,而Lambdas Expression也是.
    (2) [采集变量列表](参数列表) -> return type { 函数功能体 } //这就是表达式的组成，其中第二，第三部分可以没有，第一部分可以放空
    (3) 它能被看作是一个无名的，内联的函数(实际上它是一个有编译器生成的无名的类类型),
    但是它又可以在函数的内部定义！(想用的时候就定义),但是它的参数列表必须匹配,它没有默认参数.
    (4) 就像普通函数一样,Lambdas也拥有,参数列表,函数体,返回类型(使用新标准 (...) -> return type),
    以及独有的 [可以放空,但符号必须有] 采集变量列表.
    (5) 采集变量列表(capture list)只能使用本地的非静态变量.
    (6) capture list 在Lambdas被创建时就已经拷贝完毕(有的Lambdas并不是创建就调用),
    而不是等到调用的时候才拷贝(这一点和函数的参数传递有些不同),所以在创建之后,即使list所capture的变量被更改,对此也毫无影响.
  {
    int z = 0;
    auto f = [z]{ return z; };
    z = 2;
    std::cout << f() << std::endl;
    //输出0
  }
    但是,你同样可以传递引用给 capture list 这样你就能动态的使用变量的值
    使用格式: auto f = [&z]{ ... };
    (7) 从函数返回一个Lambdas是合法的.(记住,不要返回一个本地变量的引用,非法,尤其是在使用capture list时).
    (8) [=]代表隐式的capture全部本地变量,[&]代表隐式的capture所有的本地变量,并用引用传递.
    (9) 按值传递时,使用mutable关键字可以让值变得可修改.[z]()mutable{return ++z;};//此时参数列表必须出现，可以为空.
    最后,尽量少capture 指针(pointer)或者引用(reference)或者迭代器(iterator).
    /*************************************************************************/
    void te_fun(const std::string &s, size_t v){
    ...//Something Useful
    find_if(vec.begin(),vec.end(),
             [v](const std::string & s) { return s.size() > v; } );
    ...//Something Useful
   }
   /*************************************************************************/
   Lambdas Expression的返回类型可以省略,由函数体的代码自动推断(当没有return语句则为void,有一个则为返回类型,一个以上需要自己指明),也可以显式定义.
   for_each(vec.begin(),vec.end(),[](const string &s){std::cout << s << " "; });//让第三个参数,即可调用对象作用于
                                                                                //每一个范围内的项/值.
01. Binding argument{ <functional> bind }
    auto newcall = bind(call,_n,binded_arg);//_n代表newcall的第n个参数,使用前要先声明,using std::placeholders::_1;
                                            //把call的第一个参数绑定到newcall的第n个参数,把binded_arg绑定到call的第二个参数.
    通过这个特性,我们可以在不修改函数的前提下调整一个函数的参数顺序.
    我们同样不能 bind 一个不能复制的对象,例如最明显的stream对象.但是我们可以使用一个在<functional>头文件中定义的 ref() 函数
    它返回一个引用(cref()返回一个const引用)这样我们就能 bind stream了.
