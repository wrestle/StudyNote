静态类成员，Static Class Members.
00. 静态类成员更多的是与类(class)本体直接相关，而不是与类生成的独立的对象(object)相关,即static成员不依赖任何类对象存在.
01. 可共享于不同的对象.
02. 类生成的对象并不包含静态(static)成员.即每个对象只是包含(contain)【calculate函数,own字符串,amount浮点数】.
03. There is one ''interestRate'' object that will shared by all the '''Account''' object.
04. 静态成员函数，不能被声明为(const),也没有(this)指针，也不绑定任何类生成的对象(object).
05. 创建类对象的时候，静态(static)成员并不会被构造函数(consturctor)初始化.//一般来说，也不会在类体内初始化static成员
   但是，我们 必需 在类体外完成对静态(static)成员的初始化.//静态成员只能被定义(defined)一次.
06. 有一个确保静态(static)成员只被定义一次的好方法就是
   把它的定义和 非内联(inline)类成员的定义 放在同一个文件中.
07. Tip:static 成员的血量就像 globle 对象一样长，一直存在到程序结束.

08. 我们一般不再类主体(body)内初始化静态成员，但是我们有时候会提供一种 类内初始化器(in-class initializer)
   来帮助我们完成某些事情，比如数组的维数确定//维数需要 constexpr of literal type
  //static constexpr int period = 30;   这个时候，''period'' 就是constant expression.
  //Tips:当然，这里使用 const 也是可以的.毕竟C++中本来就建议使用 const 来替代 #define.
  //double arr[period];                 ok,这是可行的.
09. 即使一个(const static)成员在类主体内被初始化了，我们依旧应该在 类外 定义(define)它
    constexpr int period;//不给他初始化的值(initializer).

10. 我们可以让一个静态成员用在构造函数的形参中,让它充当默认形参,但非静态成员就不行. 第 25 行
/*******************************************************************************/
class Account{
public:
  Account(double catch = interestRate);
  void calculate(){amount += amount * interestRate;}
  static double rate(){return interestRate;}
  static void rate(double);
private:
  std::string owner;
  double amount;
  static double interestRate;
  static double initRate();
};

//我们可以在类主体(body)内直接完成定义静态成员函数 第 27 行
//也可以在类体外定义 第 40 行
//这时候我们就 不需要 再写一遍关键字 静态(static)
//它只需要出现在类体中的声明即可。
void Account::rate(double newRate)
{
  interestRate = newRate;
}

//我们可以使用initRate()给interestRate初始化，尽管它是private
double Account::interestRate = initRate();
/*******************************************************************************/

使用类静态成员,Using Class Static Menbers.
1. double r = Account::rate();//使用scope operate能够访问类静态成员.

2. Account a;
   Account *pa = &a;
   r = a.rate();
   r = pa->rate();
  // 尽管类静态成员并没有被类对象包含在内，但任然可以像正常的成员一样被类对象访问到。
