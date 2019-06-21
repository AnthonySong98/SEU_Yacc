**SEU_Yacc**的执行步骤如下：

1. 打开终端，切换当前工作目录。

2. 输入 `cmake.` `make all`，编译项目。

3. 输入`./Seu_Yacc yacc.y`，根据 `yacc.y`文件，产生语法分析器**SEU_Yacc**的C++代码文件 `yyparse.cpp`。

4. 输入 `g++ -std=c++11 yyparse.cpp -o Parser`，编译生成语法分析器**SEU_Yacc**的可执行文件。

5. 输入 `./Parser Lex_Tokens.txt `，对测试代码文件经过**SEU_Lex**得到的Token序列进行语法分析，测试**SEU_Yacc**的表现。终端可以打印出AST的结构，并且利用graphviz生成可视化AST的PDF。
