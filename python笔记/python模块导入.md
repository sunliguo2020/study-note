### 模块搜索路径
当一个spam的模块被导入时，解释器首要搜索具有该名称的内置模块。这些模块的名字被列在sys.builtin_module_names中。如果没有被找到，它就在变量sys.path给出的目录列表中搜索一个名为spam.py的文件，sys.path从这些位置初始化：
-   输入脚本的目录
-   PYTHONPATH(目录列表，与shell变量PATH的语法一样)
-   依赖于安装的默认器