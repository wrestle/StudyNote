动态内存
      //由于动态内存并没有一个具体的对象,只是一个启始指针,所以我们不能使用begin,end,也不能使用rang for

01.   new :
      int *pia = new int[get_size()];//pia指向这块连续的内存的首位.
      int *pia = new int[size]();//假设size存在且合理,pia指向这块被全部初始化为0的内存块的首位
      int *pia = new int[size]{1,2,3};//C++11新特性,如果花括号内参数个数小于size,则超出的部分初始化为0.
                                      //此特性用来弥补圆括号不能添加参数的缺陷
      string *pia = new string[size];//等同于string *pia = new string[size]();
      delete [] pia;
02.   标准库提供了一种unique_ptr版本的动态数组.
      unique_ptr<type_name []> ps(new type_name[size]);//ps可进行的操作很少,其中只包括 ps[i].
      而标准库并未给我们提供shared_ptr版本的动态数组.如果我们相用,就要自己提供适用的delete版本.
      shared_ptr<type_name []> ps1(new type_name[size],
                                      [](int *p){ delete []p;})//第二个参数是可调用对象,用来释放动态数组
                                                               //然而即便如此,shared版本的动态数组指针连
                                                               //下标运算[i],都不提供,我们只能通过 .get()
                                                               //函数来间接进行递增以此来操作元素.
      上述两种使用,都要在最后解除智能指针的绑定,ps.release(),ps1.reset().
