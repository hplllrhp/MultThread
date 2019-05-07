# MultThread
这是QT实现多线程，并且测试的工程。使用的方式有两种

- 继承QThread类，重写run函数实现多线程。
- 继承QObject类，将对象放入QThread的对象中（QT官方推荐）。

参考的教程
- [Qt使用多线程的一些心得](https://github.com/czyt1988/czyBlog/tree/master/tech/QtThread)
