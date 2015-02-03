泛型算法,Generic Algorithms.{headfile <algorithm> ::大多数泛型算法在此头文件中,还有一部分在 <numeric>}
//注:cbegin(),cend(),返回的是 const_iterator 类型的迭代器
//   begin() ,end() ,返回的是 iterator       类型的迭代器 STL中的容器使用成员函数表示法( .操作符),数组则使用参数传递方式.
//   范围有效性: 从迭代器至有效范围的最后一个迭代器之间的范围必须是有效的.
00. 泛型算法并不是直接作用于容器(container)上,而是通过操作两个绑定在一定范围内的迭代器来实现效果的.
    泛型算法是依赖于运算符(operator)的,它的运算是依据迭代器(iterator),而不是容器(container)自身支持的运算.
    因为算法 并不改变 操作容器的大小.有一个不算例外的例外就是(insertor iterator的一种),可以改变(添加)元素进
    容器,但这也是迭代器做的，而算法并没有作用.
01. 只读(Read-Only)算法{ <numeric>:accumulate <algorithm>:find ...}
    accumulate(cbegin_iterator,cend_iterator,initial_value);//initial_value即在迭代器范围内所有数字相加的结果上再加上它的值(先加它).
    find(cbegin_iterator,cend_iterator,find_value);//find_value就是要在迭代器范围内寻找的值,找到则返回位置迭代器，否则就返回cend_iterator.
    find_if(cbegin_iterator,cend_iterator,_predicate);//见04.返回第一个符合第三个参数的iterator
                                                      //需要一提的是，第三个参数只接受 一元谓语(unary predicate)即只有一个参数能传递给它.
                                                      //如果是多个参数,解决办法见05 Lambdas Expression.
    equal(cbe_seq1,cend_seq1,cbe_seq2);//比较两个顺序容器中的值是否相同.
    Write 算法{ fill...}
    fill(beg_iterator,end_iterator,Like_to_fill);//Like_to_fill是一个可以被转换为该容器内的类型的值，该范围内的值会全部被替换为它.
    fill_n(beg_iterator,range,Like_to_fill);//range是要进行的范围,但是不能超出该容器的实际范围(实际大小).
02. 插入迭代器 insert iterator {headfile <iterator>}
    back_inserter();//一个用来绑定容器的函数，使用其的目的是产生back_push()的效果.
    fill_n(back_inserter(container),range,Like_to_fill);//此时即使container是一个空容器，此语句依旧可行，而上例则不行.
03. 拷贝算法 Copy Algorithms { copy replace replace_copy...}
    copy(beg_seq1,end_seq1,beg_seq2);//此算法将范围1的拷贝到以第三个参数为开始的迭代范围中，需要确保第三个参数的范围有效性.
    replace(beg_iterator,end_iterator,changed_val,change_val);//changed_val是待替换的值(必须在容器中),change_val则是替换成此值.
    replace_copy(cbeg_iterator,cend_iterator,back_inserter(container),changed_val,change_val);
    //此算法不改变原有的容器的值，而是将改变后的结果放到另一个新的容器中保存,其他操作一致.
04. 整理算法 Reorder Algorithms { sort }
    sort(beg_iterator,end_iterator);//按照升序整理
    sort(beg_iterator,end_iterator,_predicate);//说白了就是把前两个参数所经过(travese)的项/值,传递给第三个参数达到sort的效果,
                                               //这种重载就是为了某些不能直接比较的类型(比如自己定义的).
    stable_sort(beg_iterator,end_iterator,_predicate);//这个算法的大部分动作和sort一样，参数个数也一样，唯一不同的是在
                                                      //当遇到相同的两个项/值时，sort可能交换两个元素的位置,即保持相同项/值原有的相对位置.
    unique(beg_iterator,end_iterator);//注意，做用后会改变原容器的内容,其作用是:
                                      //非重复的项迁移至前方，覆盖或停留重复的项，返回一个iterator,指向最后一个不重复项的后面一项.
05. Lambdas Expression
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
06. Binding argument{ <functional> bind }
    auto newcall = bind(call,_n,binded_arg);//_n代表newcall的第n个参数,使用前要先声明,using std::placeholders::_1;
                                            //把call的第一个参数绑定到newcall的第n个参数,把binded_arg绑定到call的第二个参数.
    通过这个特性,我们可以在不修改函数的前提下调整一个函数的参数顺序.
