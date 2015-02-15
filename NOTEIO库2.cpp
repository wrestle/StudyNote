 IO Library {<iostream> <fstream> <sstream>}
             istream    ifstream  istringstream
             ostream    ofstream  ostringstream
             iostream   fstream   stringstream

00. 流(stream)无法被拷贝(copy)，所以它无法被当作参数以及返回值，也不要声明成(const)，
    因为 IO 对象(object)经常改变自身状态(state).
01. 我们常在函数中看见流(stream)的身影，他们的使用方式是“引用(reference &)”,这样就能充分发挥流的作用而不被限制.
02. 由于人为或机器导致的错误，会让(cin)之类的操作的状态(state)设置为错误(error),当且仅当
    流(stream)处于无错(non-error)状态下，才能对它进行读取或者写入.//常见判断whiile(cin >> word)...
03. 每个输出流(output stream)都管理着一个缓冲区,由于输出对硬件来说是一件耗时的事情，
    所以只有当以下情形才会输出:
      ·程序正常完成.
      ·缓冲区满了.
      ·显式使用控制器(manipulator)比如 std::endl.
      ·人为使用控制器 unitbuf 让每次输出操作结束以后清空(flush)缓冲区，默认情况下，这个控制器为cerr设置。
      ·如果一个输出流被绑定在别的输出流上，每次操作都将会清空缓冲区，例如cin和cerr被绑定在cout上，每次cin
      和cerr操作都将会清空cout的缓冲区.
04. unitbuf的用法，以及nounitbuf.
    std::cout << std::unitbuf;          //输出会被立即清空(flush)，不被缓冲(buffer).
    std::cout << std::nounitbuf;        //重新设置为有缓冲的状态.
    //Tips: 如果程序不正常终止(terminate abnormally),缓冲区不会被清空.
05. 绑定的用法，关键字(tie)
    cin.tie(&cout);        //只是演示，因为默认这俩就是绑定的.
    ostream *old_ptr = cin.tie(nullptr);
    cin.tie(old_ptr);      //恢复默认
//fstream
06. ifstream input(str,mode);//创建一个对象，类型是ifstream,继承自istream. str代表字符串(也可以是C-Style字符串)，
                             //mode代表打开模式，mode也可以不写，默认为打开文件流.
    ofstream output(str);    //创建一个对象，类型是ofstream,继承自ostream. str代表字符串(也可以是C-Style字符串),并打开该文件.
    input.close();           //关闭文件
    input.open(str + ".ME"); //打开另一个文件
    output.close();
    output.open(str + ".txt");  //同上
    //如果打开成功，那么流的成员函数good() 的返回值将会是true.
    //如果一个fstream对象被销毁(destroyed),那么close()函数会被自动调用.
07. 对于命令行状态下,int main(int argc,char* argv[]) 中,argc代表命令后有几个参数，argv[argc] == NULL;从argv[1]开始，到
    argv[argc]之前，为命令之后的参数名(以字符串形式传递).argc[0] 保存着命令的名字或者是一个空字符串.
08. 模式{in out app trunc ate binary}
    {
     ifstream::in    是 ifstream对象打开时的默认模式
     ofstream::out   是 ofstream对象打开时的默认模式，该模式自带 trunc 模式功能.
     ofstream::trunc 的功能是截断，即删除打开文件里的所有内容，等待输出.
     ofstream::app   确保原有内容不被删除. //相当于 ofstream::out | ofstream::app
    }
//stringstream
09. 把string看作是一个IO stream 是这个存在意义.istringstream读取一个string,ostringstream写入一个string.
    stringstream同样是继承自iostream.
    istringstream 主要用于以行为单位的读入.
    while(getline(cin,line))
    { string word;
      istringstream record(line);//把读取的行 line 绑定在 istringstream 类型的record上.
      while(record >> word) { cout << "Read a Word!: " << word << endl;}
        //从 line 中每读取一个字符串,就输出提示,以空格为界限.
    }
