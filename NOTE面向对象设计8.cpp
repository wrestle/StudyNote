面向对象 Object-Oriented
  //数据抽象(Data abstraction), 继承(inheritance), 动态绑定(Dynamic Binding)
  //分离接口和实现, 相似类型建立相关模型, 直接使用不同类型的对象而不去考虑他们的区别
  //继承能够继承父类(base class)的pubkic 和 protected 成员,private不能被继承只能通过接口访问.
  //对于非继承的外来对象只能访问public对象.
  //声明继承类的时候不必加上从哪里继承这个细节,它应该出现在类定义,而不是类声明.
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
      class1 temp1; deri_class1 temp2; //前者是基类后者是继承类
      class1* p = &temp1;              //毫无疑问
              p = &temp2;              //这样也行
      class2& t = temp2;               //可以
      "...we can use a pointer to a derived type where a pointer to the base type is required."
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
