关联容器 Associative Container {四种非顺序容器 和 四种顺序容器}
(1) 顺序容器的键必须是可以用'<'运算符比较的,否则就要自己提供比较函数进行整理(order)
    顺序容器包括{ map , set , multiset , multimap };
(2) 关联容器一般不使用泛型算法(Generic Algorithms)
01.   map用来保存一对 键-值(key-value) 索引时,可用键来进行索引(下标操作[str])对应的值,但切记,键一定是唯一的(初始化时注意)
      map系列容器所提供的下标操作和一般数组或者vector有所不同,key可以是不存在的,但是数组和vector却不幸.
      map<string, value_type>map_name; //一个空的map,从string指向特定类型的值.
      ++map_namp[str];                 //使用时如同数组一般进行添加,此处假设str为string类型,value_type是int
      /*
          map<string,string> map_name
        { {"Mother" ,"Father"},{"Dad" ,"Mon"},{"Dady" ,"Momy"} }; //也可以这样列表初始化
      */
                                       //实际上每个 map 的元素都是一个模板类型(pair),包含两个数据成员 first 和 second
      for(auto &w : map_name)         // w 就是map的元素
      { cout << w.first << " : " << w.second << endl;}// w.first代表键(key), w.second代表值(value).
02.   set值用来保存键(key),我们可以这么使用它:
      set<string> set_name {"the", "and", "or"};
      if(set_name.find(check_word) == set_name.end()) {...}
03.   multimap,multiset的键就不是唯一,就像一个字典中,一个相同的字(key)可以有不同的解释(value).
      vector<int> ivec{1,1,2,2,3,3,4,4,5,5,6,6,7,7};  //14个元素
      set<int> iset(ivec.begin(),ivec.end());         //7个元素
      multiset<int> miset(ivec.begin(),ivec.end());   //14个元素
04.   当我们用自己定义的类型来使用这四种顺序关联容器时,我们必须提供可以用来排序整理(order)的可调用对象.
      multiset<My_class, decltype(class_comp)*> my_set(class_comp); //这里,class_comp是自己定义的用来比较
                                                                    //My_class类型的函数.我们提供函数指针.
      前面说过 map系列 的元素的类型是 pair,pair是一个模板类型,包含两个数据成员,分别是键和值,即:
      map_name<type1, type2>::value_type v; //这里v的类型是 pair<const type1, type2>
      map_name<type1, type2>::key_type v;   //这里v的类型是 const type1,之所以是const,是因为键是不可改变的
      map_name<type1, type2>::mapped_type v;//这里v的类型是 type2.
                                            //前两者是 map 和 set 系列容器都有定义的(包括其他四种无序的非顺序关联容器)
                                            //第三个则是只有 map系列容器才有定义
      对于 set系列 的元素类型 value_type 和 key_type 是一样的,且都是 const .
05.   添加元素进顺序关联容器{map, set}使用 .insert() 成员函数.
      set_name.insert(vec.begin(),vec.end()); //假设vector<int> vec = {1,2,3,4};
      set_name.insert({1,2,3,4});             //建设set的类型是int,记得花括号.
                                              //由于map容器的元素是 pair 类型,所以在插入之前要先转换或者构造.
      map_name.insert({"Dad",44});            //假设map容器是 map<string,int>
      map_name.insert(make_pair("Dad",44));   //make_pair()是一个已在头文件中定义的函数,用来生成pair对象.
      map_name.insert(pair<string,int>("Dad",44));
      map_name.insert(map<string,int>::value_type("Dad",44));
      .insert()成员函数返回一个pair对象,包含两个成员,
        first成员是一个指向被插入元素的迭代器(itreator). 类型为 map<string,int>::iterator
        second成员是一个bool类型,用来显示是否插入成功.   类型为 bool
06.   添加元素进顺序关联容器{multimap, multiset}同样适用 .insert() 成员函数.
      .insert()成员函数在此处返回一个指向被插入元素的迭代器(iterator).//此时不再返回pair类型.
      没有必要返回一个bool类型,因为 multi 容器必定成功插入.
07.   删除元素 .erase()
                      //当参数为 key_value 类型时,删除该key及所关联的value,并返回删除个数.
                      //当参数为 pair型iterator时,删除指向该iterator的元素,并返回其下一个iterator或者end().
08.   .count() / .find() 用来计数和查找
      前者计算并返回这个容器中key出现的次数,
      后者查找key,并返回指向该key的(第一个)iterator或者end().//之所以是第一个,是因为某些容器可能为 multi
      凭此我们可以遍历出某个key的所有键-值(key-value).
      ------------------------------------------------------
      auto f = container.find(key);
      auto c = container.count(key);
      while(c) {cout << f->second << endl; f++; c--;}//方法1
      ------------------------------------------------------

09.   .lower_bound() / .upper_bound() / .equal_range() 用来找key的下界,上界,范围.//只适用于顺序关联容器
      .lower_bound() 返回第一个不小于key的iterator
      .upper_bound() 返回第一个大  于key的iterator
      -----------------------------------------------------------------------
      for(auto b = container.lower_bound(key),e = container.upper_bound(key);
                  b != e; ++b)
                  {cout << b->second <<endl;}//方法2
      -----------------------------------------------------------------------
      .equal_bound() 返回一个key的存在范围,类型为pair,或者end().
      -----------------------------------------------------------------------
      for(auto range = container.equal_bound(key);
          range.first != range.second;++range.first)
        { cout << range.first->second << endl; }//方法3
      -----------------------------------------------------------------------

10.   
