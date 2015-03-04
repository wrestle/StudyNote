面向对象 Object-Oriented
  //数据抽象(Data abstraction), 继承(inheritance), 动态绑定(Dynamic Binding)
  //分离接口和实现, 相似类型建立相关模型, 直接使用不同类型的对象而不去考虑他们的区别
  //继承能够继承父类(base class)的pubkic 和 protected 成员,private不能被继承只能通过接口访问.
  //对于非继承的外来对象只能访问public对象.
  //声明继承类的时候不必加上从哪里继承这个细节,它应该出现在类定义,而不是类声明.
  //如果是基类,那么只声明不定义,是不能出现在继承列表中的(class deri_cl : public base_cl...)
00.   C++11 中,我们如果不想让这个类被继承,那么可以使用关键字 final
      class base_cl {...};                     //
      class base_cl1 final {...};              //该类无法被继承了
      class deri_cl2 final : public base_cl {};//可行
                                               //后面讲介绍函数的 final 关键字
01.   使用关键字 virtual 声明定义的函数, 叫做虚函数, 用于使用功能 动态绑定,更多的应用于继承中,
      虚函数在调用时,使用的版本根据调用对象的类型决定(建立在继承的关系上)
      任何非静态成员函数都可能是虚函数,声明时关键字只出现一次(在声明中),

      "A base class must distinguish as virtual those function it expects its derived classes to
      override from those that it expects its derived classes to inherit without change."
02.   在面向对象设计中,不管析构函数会不会用的上,我们都应该将它添加在类中.
03.   一个继承的类必须将它想要从基类那里继承过来并且想 重写(override)的成员函数 声明(declare).
      "When the derivation is 'public' the public members of the base class become part of the
      interface of the derived class as well(implicitly)"正因如此,当我们使用基类类型
      的指针或者引用的时候,是可以指向继承类的对象.
      class1 temp1; deri_class1 temp2; //前者是基类,后者是继承类
      class1* p = &temp1;              //毫无疑问
              p = &temp2;              //这样也行
      class2& t = temp2;               //可以
      "...we can use a pointer to a derived type where a pointer to the base type is required."
      但是,反过来就不成立了.
      总结即"derived-to-base is legal,base to derived is usually illegal,with pointer and reference only"
      用人话就是继承类和基类之间的关系转换,只能用在指针或者引用上.
      然而,如果我们使用继承类对象(derived class object)给基类对象 初始化 和 赋值 时,只将继承
      类中和基类成员相同的进行拷贝,继承类独有的成员则被忽略.
04.   如果一个虚函数在继承类中没有被重写,那么它在被调用的时候会使用基类中定义的那个函数.
      在被重写的过程中 virtual 关键字不出现,C++11 标准中,我们用一个显式方法标注使用 override 关键字
      在被重写的虚函数声明的最後面(const之后).
05.   继承类的构造函数
      deri_class1(v1,v2,v3,v4): class1(v1,v2), member1(v3), member2(v4) { /*...*/ }
      //class1为基类,menber1,member2为继承类里新定义的成员
      在这个构造函数中,我们先要将先进行基类的构造函数,再给继承类的新成员初始化,以此完成继承类的构造函数
      需要注意的是,继承类的构造函数不能直接初始化(...: ...)基类的成员(虽然可以在构造函数体中给基类成员赋值)
06.   静态成员
      和普通静态成员一样,我们可以通过(::)和(.)进行访问,也可以使用this指针进行访问,无论是基类还是继承类.
07.   虚函数 Virtual Function
        1.任何虚函数都应该被定义即使没有用到,而不仅仅是声明,因为编译器没办法判断到底那个虚函数没有被用到
        2.动态绑定只有在虚函数通过指针或者引用调用的时候才能生效,换句话就是,如果虚函数是通过对象本身直接调用,
      那么就直接使用该对象版本的虚函数.(通过对象直接调用任何函数都会在编译期内绑定在该对象上,而动态绑定则是发生在运行期)
        3.继承类如果想覆盖基类的虚函数,那么参数列表的类型必须相同,返回值类型也必须相匹配(特例就是
      derived-to-base),也就是继承类的类型指针可以隐式转换为基类的类型指针.
        4.虚函数的使用过程中,我们常常弄混重覆盖和重新定义,即我们想要使用虚函数重写功能,但是由于细节
      我们却成了重新定义了一个新函数,往往这类错误难以发现,C++11 标准中的关键字(override)的作用
      就是让编译器知道我们的目的是想重写,而不是重新定义一个新函数.如果你不想让后续的继承类重写某个
      虚函数关键字(final)会起到相应的作用.
        5.如果一个基类中的虚函数有默认参数,那么最好让他的继承类中重写的虚函数的默认参数保持一致.
        6.如果一定要使用某个特定版本的虚函数,可以使用域操作符(::)
      pclass->deri_cl1::fun(n); //pclass为某继承类的类型指针
                                //deri_cl1为任意的该继承体系中的继承类,也可以时基类
                                //fun() 为使用的虚函数
                                //一般成员函数或者友元函数的撰写需要这个机制.
08.   抽象基类 Abstract Base Classes
        1.对于面向对象设计来说,最主要的就是抽象出共性,为继承类建造一个基石,纯虚函数(pure virtual function)
      就是一个很重要的定义,凡是拥有纯虚函数的类,都无法生成对象,它的继承类可以生成对象(因为继承类重
      写了纯虚函数).
      class Disc_quote : public Quote {
            double net_ptice(std::size_t n) const = 0 }//此处的 = 0 即代表该函数为纯虚函数
        2.protected 成员的使用权限介于 public 和 private :
       它(们)不能被类使用者进入,即对象.
       它(们)只能被本类成员或者本类的友元访问.
       如果在一个继承类中,从基类继承过来的基类的protected成员只能通过基类的继承对象访问(deri_cl::pro_mem),而
      不能使用基类(base::pro_mem).[通俗的说就是只能用自己的,不能用别人的,即使那个别人是自己的基类.就像你银行卡
      的钱是你父母给的,你可以随意用这些到手的钱,但是你不能随意使用你父母卡里的钱]
        3.在面向对象设计中,我们在两个地方使用 (public, protected, private) 一种是成员声明
      另一种则是类的继承,public 代表正常继承可继承的成员(public 和 protected),private 代表
      继承所有可继承的成员,并将他们变成private 成员.[protected 同理.]
        4.友元(friend)关系无法被继承,也无法被迁移(transitive),例如基类的友元类无法拥有特权访
      问继承类的(protected, private)成员.但是访问基类的(protected, private)成员还是可以的,
      即使是在继承类对象中(即继承过来的成员可以由这个友元类访问).总之只要是属于基类的成员,友元类都能
      访问,即便是被继承了,但是继承类自己新的成员无法被该友元类访问.
        5.class base{public:    std::size_t size() const {return n;}
                     protected: std::size_t n;}
          class deri : private base{//此处使用private,所有继承成员转为private
           public: using base::size;//但是这里我们使用using关键字,重新调整了继承成员的
        protected: using base::n;   //使用权限,这是可行的.
      }                             //注:不一定需要按照原来的权限.
        6.一个类的成员(类声明定义而不是继承来的)只可能由它自己或者其继承类访问,若是类拥有基类,其基类
      是无法访问该类独有的成员的,因为成员搜索机制无法找到该成员(在动态绑定时需注意):
      deri de_cl;             //deri为base的继承类
      deri* de_clp = &de_cl;  //假设deri中定义了一个public接口 test()
      base* ba_clp = &de_cl;
      de_clp->test();         //可以
      ba_clp->test();         //不行!!因为成员搜索机制在base类中找不到test这个成员
                              //即使de_clp 和 ba_clp值相等,但类型不同.
