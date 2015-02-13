动态内存 // #include <memory>
        //我们的程序使用静态内存和堆内存 static and stack memory
        //静态内存用于 static对象 和 定义于任何函数之外的变量
        //堆  内存用于 任何定义于函数中的变量
01.   C++11标准中,为我们提供了几个方便的 智能指针(自动删除它所指向的对象和重要的异常),他们像容器一样,就是模板
    智能指针在创建时，如果不指定初始化，那么默认为 nullptr.
      shared_ptr, unique_ptr, weak_ptr(一个被shared_ptr管理的对象的弱引用(weak reference))
02.   shared_ptr<type_name> pointer_name;//创建的语法.
      shared_ptr<string> ps; shared_ptr<vector<string>> pcon;//第二个语句在c++11之前是不可取的会报错，不是因为语法，而是因为少了空格。
      我们一般这么用: auto p = make_shared<string>('a');//make_shared()是一个模板函数,用法就如前方所示,返回一个shared_ptr类型
      shared_ptr<string> p1;//编译通过
      shared_ptr<string> p1(new string("Hello"));//编译通过
      shared_ptr<string> p1 = new string("Hello");//这样就是错误的,智能指针无法接受隐式转换(从内建的指针转换为智能指针).
                                                  //同样的,不能隐式的从智能指针转换为内建指针.
      实际上，(假设只有一个shared_ptr指针指向某个对象)当p不再指向那个对象时,那个对象就会被自动释放.这就是智能指针
      把一个shared_ptr<type_name>类型的指针当作函数返回值返回时,即使它是在函数中定义的(成为本地变量),他也不会被销毁(destroy)
    因为返回的时候就是在复制它,复制会让其中的特定机制生效而保存它(这种机制就像是计数器,记录还有多少在指向这个对象)。
      ps.use_count() 返回ps指向的对象有多少个shared指针在使用.
      ps.unique() 当上面那个函数返回值是1时返回 true 否则就是 false.
      ps.get() 得到智能指针的指针值,相当于转换为普通指针,但是千万不要将它用来初始化或者赋值给另一个智能指针,这个函数被设计出来的
    意图就是为了在某些智能传递普通指针的函数使用,而且函数不应该包含释放它的操作.
      ps.reset(new int(1000)) 用来将一个智能指针指向一个新的对象 
      如果把shared_ptr<type_name>类型放进容器中,切记要在不需要的时候对它们进行 erase 操作.
03.   new :
      一般情况下我们这么用    int *p1 = new int();//代表创建一个p1指针,指向一个无名的 0 value.
                             int *p1 = new int;//则*p1是为定义的
                             int *p1 = new int(42);//代表指向一个无名的 42 value.
                             const int *p1 = new const int(100);//同理,只不过是多了一个const
      更直接的是             int *p1(new int(1000));//同理
      在C++11中我们可以这么用 auto p1 = new auto(value_obj);//若value_obj类型是int 则p1类型为 int*.
04.   对于智能指针 shared_ptr 时,更加推荐使用 make_shared();函数,而少用 new 关键字.
      原因是 当普通指针被复制,赋值,等行为时,并没有一个 “计数器” 来记录有多少个相同的指针指向了其所指向的对象.那么
      int *x(new int(20));
      func_cal(shared_ptr<int>(x));//此时出现了智能指针,那么它的计数器就会加1,表示有多了
                                   //一个指向保存有 20 的内存.
                                   //那么一旦这个函数结束后呢？
      int i = *x; //错误！！因为这个内存位置已经被释放了！因为计数器递减为0,智能指针认为此处的内存已经没有用了。
      所以,不要把普通指针和智能指针混合在一起使用,一旦我们将普通指针转换为智能指针,实际上就是把内存管理的责任由
      我们程序员转交给了程序.
