**SEU_Yacc**的执行步骤如下：

1. 打开终端，切换当前工作目录。

   ![image-20190604005908299](/Users/mac/Desktop/编译原理课程设计/graph/mdpic/image-20190604005908299.png)

2. 输入 `cmake.` `make all`，编译项目。

   ![image-20190604005954351](/Users/mac/Desktop/编译原理课程设计/graph/mdpic/image-20190604005954351.png)

3. 输入`./Seu_Yacc yacc.y`，根据 `yacc.y`文件，产生语法分析器**SEU_Yacc**的C++代码文件 `yyparse.cpp`。

   ![image-20190604010018626](/Users/mac/Desktop/编译原理课程设计/graph/mdpic/image-20190604010018626.png)

4. 输入 `g++ -std=c++11 yyparse.cpp -o Parser`，编译生成语法分析器**SEU_Yacc**的可执行文件。

   ![image-20190604010152034](/Users/mac/Desktop/编译原理课程设计/graph/mdpic/image-20190604010152034.png)

5. 输入 `./Parser Lex_Tokens.txt `，对测试代码文件经过**SEU_Lex**得到的Token序列进行语法分析，测试**SEU_Yacc**的表现。终端可以打印出AST的结构，并且利用graphviz生成可视化AST的PDF。

   ![屏幕快照 2019-06-21 下午11.56.03](/Users/mac/Desktop/屏幕快照 2019-06-21 下午11.56.03.png)
