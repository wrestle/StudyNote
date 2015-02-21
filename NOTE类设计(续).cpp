类设计 Class Design
01.  new 和 delete 包含四个操作:(分配内存 构造对象) (析构对象 释放内存)
     有时候我们只是在需要的时候才使用,所以我们把 new 的操作分开(decouple),因为 new 往往会浪费一些内存
     而且更重要的是,一个没有默认构造函数的类,是不能动态分配成一个数组的.
     ·引入 allocator Class.<memory>
     allocator是一个模板类,用来分配一种未被构造的,生(raw)的内存块,通俗地说就是,这块地皮被买下了,但还未建任何东西.
     allocator<type_name> alloc;                 //创建一个allocator对象
     auto const ptr = alloc.allocate(obj_num);   //分配obj_num个对象的存储空间,此时还未construct,称为unconstruct.
                                                 //之所以声明为const, 是为了防止首位指针无法找到

     auto ptr_in = ptr; alloc.construct(ptr_in++,type_value); 
     allocator支持{ .allocate(n); .deallocate(p, n); .construct(p, args); .destroy(p); }
      其中, n(n个对象长度), p(由allocate返回的一个指针) args(参数列表,有的类的构造函数不止一个参数)
     args这个是C++11的新特点,之前版本只允许一个参数,而不允许多个参数的args参数列表.
02.  ·和指针使用一样,我们不能destroy unconstruct的内存,不能把null指针传递给 deallocate();
     ,就像不能 delete null 指针.
