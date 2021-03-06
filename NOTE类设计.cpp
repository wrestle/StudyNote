类设计 Class Control
      //对于类设计来说,只声明不定义是可行的合法的.任何想使用这个未定的功能的行为都会在编译时期被判定为错误.
      //拷贝, 移动, 赋值, 销毁(析构函数)
      //其中移动构造函数 移动赋值构造函数是新标准下的产物
      //拷贝构造函数  拷贝赋值构造函数 移动构造函数 移动赋值构造函数 析构函数
      //这五种函数并不是都要被定义,而是有选择性的定义一个或者更多个.
      //一个类如果需要析构函数,那么它一般(很大概率)需要拷贝构造函数 和 拷贝赋值函数.
      //    比如,一个类成员是由动态内存分配产生的,那么当它被当作右值赋值的时候,编译器默认拷贝的是
      //    指针的值,即两个对象共享一个内存块(叫做pointerlike),当赋值结束后,这个内存即被销毁.两个对象都会被销毁,
      //    就是delete同一个内存两次,这种行为是未定义的(undefine).
      //如果一个类需要一个拷贝构造函数,那么它一般(很大概率)需要一个拷贝赋值构造函数.反过来亦是
01.   拷贝构造函数(声明时) 只有当第一个参数是本类型的引用(copy constructor),其他参数都拥有默认的值的时候.
      拷贝初始化(Copy initialization)使用拷贝构造函数或者移动构造函数,它把右值操作数拷贝给那个被创建的对象
      直接初始化(Direct initialization)则是让编译器自己选择合适的匹配函数来创建函数.
02.   拷贝赋值构造函数 就是一个重载的运算符(operator)
      它的作用就是把右值(right-hand)的每一个非静态成员赋给(assign to)左值对象(left-hand object),数组则把其中
      每一个元素都赋给左值,而不仅仅是拷贝地址.
      如果没有显式定义拷贝赋值构造函数(Copy-Assignment Constructor),那么编译器自己生成.
      ------------------------------------------------------------------------------
      M_class& M_class::operator=(const M_class &rhs)
     {
       name = rhs.name;
       age  = rhs.age;
       return *this;
     }
     --------------------------------------------------------------------------------
03.  析构函数是与构造函数相反的一种行为,由于它没有参数,所以它无法被重载,也就是每个类中析构函数只有一个
     析构函数销毁(destroy)非静态成员的顺序和构造函数创建非静态成员的顺序相反.
     内建的类型(build-in type)不需要析构函数
     当引用和指针出了所在的代码块,他们不会自动的引发析构函数.
04.  C++11中 = default
     我们只能将它用在有编译器自动生成的函数中,如各类构造函数.
     当我们在类声明中给成员函数加上 = default,那么就是让 编译器去生成这个函数,并且设为内联.
     当我们在类成员的定义的时候加上 = default,那么就是让这个函数不是内联.其他与上句相同.
     class Mclass{public: Mclass() = default; Mclass &operator=(const Mclass&rhs);};
     Mclass& Mclass::operator=(const Mclass&rhs) = default;
05.  C++11中 = delete 让我们能够关闭某些类功能,如拷贝复制.
     C++11之前,我们想关闭某些功能只能将其声明为 private, 并且不定义它.
     = delete 必须出现在类的声明中,并且能用在类的任何函数上,但是不要在析构函数上使用它.
     如果类中的成员无法(默认构造, 拷贝, 赋值, 销毁),那么该类也会对他的相应成员函数进行 = delete
     如果一个类成员是 const 或者 引用, 那么他的拷贝赋值运算符( = ) 会被自动的 = delete.
06.  对于拷贝复制我们有两种理解,一直从 C 语言延续,
     (pointerlike)共享对象(多个类对象共用一个存储内存),
     (valuelike)独立对象(不同类对象使用不同的存储内存),一般情况下我们都希望在赋值,拷贝的时候出现的是valuelike.
     为了实现它,我们需要完善三个方面:
     (1) 一个(copy constructor),拷贝整个内存块,而不仅仅是拷贝内存地址.
     (2) 一个(destructor)去释放我们动态分配内存块.
     (3) 一个(copy-assignment operator)去拷贝它的右操作数,并且释放现存的对象内存
         具体的是,先释放左值对象(此处以及后续的左值右值是相对于该运算符来说),将右值对象的数据拷贝赋给左值,
         最后释放右值对象.
         我们需要注意的是当把自身赋值给自身时的正确性.为此我们可以自己定义自己的运算符(最好都如此).
             具体操作流程是: 先在本地创建一个临时对象保存右值的对象,这时候可以放心的释放左值,释放完左值将保存的
             本地对象拷贝赋值给左值对象,最后释放右值对象.
07.  在交换两个类对象的时候,并且有动态内存分配的成员时,我们通常是想到创建分配一个临时对象(内存块)来当"中转站",但
     这样不仅耗费时间也耗费内存,不妨只交换指针而不是交换对象:
        void swap(Mclass &rh1, Mclass &rh2) //此为友元函数,也可以作为类成员函数,也就是不自然罢了.
      {                                     //假设此类中有一个 std::string 数据成员 str
        std::string *temp = rh1.str;
        rh1.str = rh2.str;                  //或者可以使用 std::swap() 算法来进行交换
        rh2.str = temp;                     //using std::swap; swap(rh1.str,rh2.str);
                                            //此处std::swap()可以在这个函数中工作,而不产生冲突.
      }
     //虽然 swap 函数并不是一个类的必要成分,但是swap可以让类更好的管理和分配内存.
     //还有一点便是,尽量自己定义 swap 而不是直接使用 std::swap();
