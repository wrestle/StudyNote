一些非容器定义的iterator:
  (1). Insert  iterator : 可以改变容器大小的迭代器
  (2). Stream  iterator : 绑定在输入输出流上并控制他们所关联的 IO stream.
  (3). Reverse iterator : 可以向后移动的迭代器,并不是所有容器都有.
  (4). Move    iterator : 移动容器中的元素
(1). Insert iterator {back_inserter,front_inserter,inserter}
00.  back_inserter创建一个使用push_back()的iterator
     front_inserter创建一个使用push_front()的iterator
     inserter创建一个使用两个参数的insert()的iterator,并且将值插入参数中提供的 用于定位的iterator 之前的一个位置.
     Insert iterator 支持两类的运算: inserter1 = value;*inserter1 || ++inserter1 || inserter1++
     特例: { *it = value } == { it = insert(it ,value);++it;}//假设 it 是inserter创建的.
                                                             //原因是我们要让it始终指在最初的值上.
(2). iostream iterator
01.{
     istream_iterator<int> ini_it(std::cin),eof;
     vector<int> vec(ini_it,eof);//iterator的一个小技巧.
   }//将标准输入中的值加入到vec容器中直到无效输入.
   同样,我们也可以把它们用在泛型算法里.
02. ostream_iterator<int> outp(cout, " ");//每次输出的时候加一个空格在后面.
     for(auto e : vec)
       *outp++ = e;//其实在此处我们可以不用如此写,因为后缀递增和前缀递增 解引用 对ostream_iterator仅仅只是作用
                   //但并没有实际效果
                   //outp = e;效果一样.
(3).  Reverse iterator
04. 由rbegin(),rend(),crbegin(),crend()返回,当对此种迭代器做递增操作时,它产生的效果是使该迭代器向当前位置之前的位置移动.
    但是需要注意的是forward_list 和 stream 是不可以生成reverse iterator的.
05. 记住,reverse iterator是相反方向的,打印的顺序也是! .base()成员函数能有逆转它成员正常的iterator.

任何算法的大部分性能来自传递的(pass)iterator提供的操作,能分为五大类
{Input iterator/Output iterator/Forward iterator/Bidirectional iterator/Random-access iterator}
而传递一个错误(lower than validity)等级(hierarchy)的iterator是一个错误,因为它不能正确的提供应有的功能.
例如replace_copy() 需要写(write)操作,但是你传递给他一个只读的iterator就会造成错误,但很多编译器不会报错.

同样的只读的iterator最好用在 single-pass 的算法,即只允许iterator的作用发生在算法上,而不允许算法的作用发生在iterator的目标上.
算法命名的意义: 有的算法拥有另一个版本,比如find() find_if()，他们实现相似的功能,但是行为不同,之所以不用重载是为了防止二义性的发生
_if   : 函数名字后跟_if表示 当此参数的返回值为true时,此算法成立.
_copy : 函数名字后面跟_copy表示,算法作用的结果并不返回输入容器(或者输入迭代器),而是在另一个位置(destination)输入.
