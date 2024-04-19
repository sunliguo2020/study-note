文章目录
一、logging.config.fileConfig()
二、logging.config.dictConfig()
在python中进行日志配置时，除了在 Python 代码显式创建日志器、处理器和格式器外，在实际项目中更多的是通过读取配置文件来完成日志配置的。

在python内置的logging.config模块中，有两个常用的方法：fileConfig()、dictConfig()

接下来将总结如何使用这两种方法进行日志配置

一、logging.config.fileConfig()

```python
logging.config.fileConfig(fname, defaults=None, disable_existing_loggers=True, encoding=None)
```

该方法可以从符合ini格式的文件中读取日志配置（configparser — 配置文件解析器 — 受支持的 INI 文件结构）

fname 参数指定 文件名或文件类对象；

disable_existing_loggers 设置为True时（默认），表示将禁用任何现有的非根日志器，除非它们或它们的祖先在日志配置中被显式命名。设置为False时，表示在调用该方法时，不会禁用已有的日志器。

示例：

log.ini

```
[loggers]
keys=root,fileLogger,trFileLogger

[handlers]
keys=consoleHandler,fileHandler,trFileHandler

[formatters]
keys=consoleFormatter,fileFormatter

[logger_root]
;level=DEBUG
handlers=consoleHandler

[logger_fileLogger]
level=DEBUG
handlers=consoleHandler,fileHandler
qualname=fileLogger
propagate=0

[logger_trFileLogger]
level=INFO
handlers=consoleHandler,trFileHandler
qualname=trFileLogger
propagate=0

[handler_consoleHandler]
class=StreamHandler
level=DEBUG
formatter=consoleFormatter
args=(sys.stdout,)

[handler_fileHandler]
class=FileHandler
level=DEBUG
formatter=fileFormatter
args=('./FH.log', 'a', 'utf8', True)

[handler_trFileHandler]
class=logging.handlers.TimedRotatingFileHandler
formatter=fileFormatter
kwargs={"filename":"./trFH.log","when":"S","interval":1,"backupCount":3,"delay":True}

[formatter_consoleFormatter]
format=[%(asctime)s - %(name)s] %(message)s
datefmt=%Y-%m-%d %H:%M:%S

[formatter_fileFormatter]
format=[%(asctime)s - %(name)s - %(filename)s:%(lineno)d] %(message)s
```


python代码读取日志配置文件，并记录日志：

```python
import logging
import logging.config

# import logging.handlers

logging.config.fileConfig("./log.ini")

logger_r = logging.getLogger()
logger_f = logging.getLogger('fileLogger')
logger_ft = logging.getLogger('fileLogger.test')
logger_trf = logging.getLogger('trFileLogger')

logger_r.warning(logging.getLevelName(logger_r.getEffectiveLevel()))
logger_r.warning(logger_r.parent)

logger_f.info(logging.getLevelName(logger_f.getEffectiveLevel()))
logger_f.info(logger_f.parent)

logger_ft.info(logging.getLevelName(logger_ft.getEffectiveLevel()))
logger_ft.info(logger_ft.parent)

logger_trf.info(logging.getLevelName(logger_trf.getEffectiveLevel()))
logger_trf.info(logger_trf.parent)

```


运行代码，输出：

# console 输出
[2023-08-18 20:25:46 - root] WARNING
[2023-08-18 20:25:46 - root] None
[2023-08-18 20:25:46 - fileLogger] DEBUG
[2023-08-18 20:25:46 - fileLogger] <RootLogger root (WARNING)>
[2023-08-18 20:25:46 - fileLogger.test] DEBUG
[2023-08-18 20:25:46 - fileLogger.test] <Logger fileLogger (DEBUG)>
[2023-08-18 20:25:46 - trFileLogger] INFO
[2023-08-18 20:25:46 - trFileLogger] <RootLogger root (WARNING)>

# FH.log 文件
[2023-08-18 20:25:46,084 - fileLogger - logger.py:20] DEBUG
[2023-08-18 20:25:46,084 - fileLogger - logger.py:21] <RootLogger root (WARNING)>
[2023-08-18 20:25:46,084 - fileLogger.test - logger.py:23] DEBUG
[2023-08-18 20:25:46,084 - fileLogger.test - logger.py:24] <Logger fileLogger (DEBUG)>

# trFH.log 文件
[2023-08-18 20:25:46,084 - trFileLogger - logger.py:26] INFO
[2023-08-18 20:25:46,084 - trFileLogger - logger.py:27] <RootLogger root (WARNING)>


解释：

log.ini文件中包含 [loggers], [handlers] 和 [formatters] 等小节，它们通过名称来标识文件中定义的每种类型的实体。对于每个这样的实体，都有单独的小节来标识实体的配置方式。

例如： [loggers] 小节中名为 root 的日志器，相应的配置详情保存在 [logger_root] 小节中。 类似地，对于 [handlers] 小节中名为 consoleHandler 的处理程序，其配置将保存在名为 [handler_consoleHandler] 的小节中，而对于 [formatters] 小节中名为 consoleFormatter 的格式化器，其配置将在名为 [formatter_consoleFormatter] 的小节中指定。

根日志器的配置必须在名为 [logger_root] 的小节中指定，并且至少要指定一个处理程序。

level用来设置当前日志器的日志级别，可选值：DEBUG, INFO, WARNING, ERROR, CRITICAL或 NOTSET，其中NOTSET表示将会记录所有消息。

handlers用来指定处理程序，如果指定多个处理程序，则各处理器用,隔开。并且指定的处理程序，必须出现在[handlers]小节的配置中。

程序中调用根日志器是通过logging.getLogger()，不传任何参数。

[logger_fileLogger]、[logger_trFileLogger] 小节是非根日志器配置详情。

level 和 handlers 的解释方式与根日志记录器的一致，不同之处在于如果一个非根日志记录器的级别被指定为 NOTSET，则系统会咨询更高层级的日志记录器来确定该日志记录器的有效级别。

propagate 条目设为 1 表示消息必须从此日志记录器传播到更高层级的处理程序，设为 0 表示消息不会传播到更高层级的处理程序。如果不设置此项，默认propagate=1

qualname 是日志器的名称，它是应用程序中logging.getLogger()获取日志器所用的名称。而且，对于非根日志器，该项必须设置（根日志器可以省略，默认为root）

如果程序中logging.getLogger(<name>)，<name>未在配置文件中定义，则它会按层级关系向上找。例如：logging.getLogger('fileLogger.test') 配置文件中没有qualname=fileLogger.test的日志器配置，它会去找有没有qualname=fileLogger的日志器配置，如果有就使用这个配置。如果没有则继续向上找，这个例子中再向上就是根日志器了。

[handler_consoleHandler]、[handler_fileHandler]、[handler_trFileHandler] 小节是处理器配置详情。

class 用来指明实例化该处理器所使用的类名。

level 会以与日志记录器相同的方式来解读，但需要注意的是这里设置的级别如果比引用它的日志器里设置的级别还低的化，是没有意义的。

formatter 条目指明此处理程序的格式化器，如为空白，则会使用默认的格式化器 (logging._defaultFormatter)。 如果指定了名称，则它必须出现于 [formatters] 小节并且在配置文件中有相应的小节。

args 给class指明的类提供示例化时的参数，如未提供，则默认为()。需要注意提供的参数会按顺序依次赋值给类定义中同样顺序的参数，如果只有提供了一个参数，后面必须有一个, 如：args=(sys.stdout,)

kwargs 给class指定的类提供示例化时的参数，与args不同的是，它提供的是关键字参数字典，因此不需要按顺序提供参数。如未提供，则默认为{}。

[formatter_consoleFormatter]、[formatter_fileFormatter] 小节是格式化程序配置详情。

format 是整个格式字符串，而 datefmt 则是兼容 strftime() 的日期/时间格式字符串，用来指定format中的asctime（如果有）对应的日期时间格式。如果datefmt为空，则使用默认的'%Y-%m-%d %H:%M:%S,uuu'

style 用来指定格式字符串使用的类型风格，默认为 %，还支持{、$ 类型

class 用来指定格式化程序使用的类，默认为logging.Formatter

### 二、logging.config.dictConfig()

该方法从一个字典获取日志记录配置。这是Python 3.2 中，引入的一种新的配置日志记录的方法，它提供了上述基于配置文件方法的功能的超集，并且是新应用程序和部署的推荐配置方法。

传给 dictConfig() 的字典包含以下的键：

version - 应设为代表架构版本的整数值。 目前唯一有效的值是 1

formatters - 对应的值将是一个字典，其中每个键是一个格式器 ID 而每个值则是一个描述如何配置相应Formatter 实例的字典。

Formatter实例字典，可选键有：format、datefmt、style、class

filters - 对应的值将是一个字典，其中每个键是一个过滤器 ID 而每个值则是一个描述如何配置相应Filter实例的字典。

Filter实例字典，可选键有：name

- handlers - 对应的值将是一个字典，其中每个键是一个处理器 ID 而每个值则是一个描述如何配置相应Handler实例的字典。

  Handler实例字典，必选键：class，可选键：level、formatter、filters，所有其他键将作为关键字传递给class指定的类，如：logging.handlers.RotatingFileHandler类，需要的参数filename、maxBytes、backupCount等。

loggers - 对应的值将是一个字典，其中每个键是一个日志记录器名称而每个值则是一个描述如何配置相应Logger实例的字典。

Logger实例字典，可选键有：level、propagate、filters、handlers

root - 根日志记录器对应的配置。 配置的处理方式将与所有日志器一致，除了propagate 设置将不可用之外。

incremental - 配置是否要被解读为在现有配置上新增，该值默认为 False。这个不太容易解释，暂时忽略。

disable_existing_loggers - 是否要禁用任何现有的非根日志记录器。 该设置对应于 fileConfig() 中的同名形参。 如果省略，则此形参默认为 True。

示例：

你可以使用JSON格式的配置文件，或使用YAML格式的文件来填充配置字典，其中YAML文件作为配置文件，算是目前比较主流的用法，这个示例也以YAML文件作为配置文件。

关于YAML的更多信息请参考：【YAML知识】YAML 简介及语法，绝对干货

log.yaml

version: 1
disable_existing_loggers: false
formatters:
  simpleFormatter:
    format: '[{asctime}.{msecs:03.0f} - {name} - {levelname}] {message}'
    datefmt: '%Y-%m-%d %H:%M:%S'
    style: '{'
handlers:
  consoleHandler:
    class: logging.StreamHandler
    level: DEBUG
    formatter: simpleFormatter
    stream: ext://sys.stdout
  fileHandler:
    class: logging.handlers.RotatingFileHandler
    level: DEBUG
    formatter: simpleFormatter
    filename: sample.log
    maxBytes: 80
    backupCount: 3
loggers:
  sampleLogger:
    level: DEBUG
    handlers: [fileHandler, consoleHandler]
    propagate: no
root:
  level: INFO
  handlers: [consoleHandler]

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
python代码读取配置文件，并记录日志：

import logging.config
import yaml

with open('./logconf/log.yaml', 'r') as f:
    config = yaml.safe_load(f.read())
    logging.config.dictConfig(config)

logger_r = logging.getLogger()
logger_s = logging.getLogger('sampleLogger')

logger_r.info(logger_r.getEffectiveLevel())
logger_r.warning(logger_r.parent)

logger_s.info(logger_s.getEffectiveLevel())
logger_s.warning(logger_s.parent)
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
运行代码，输出结果：

# console 控制台输出
[2023-08-18 23:52:43.016 - root - INFO] 20
[2023-08-18 23:52:43.016 - root - WARNING] None
[2023-08-18 23:52:43.016 - sampleLogger - INFO] 10
[2023-08-18 23:52:43.016 - sampleLogger - WARNING] <RootLogger root (INFO)>

# sample.log 文件
[2023-08-18 23:52:43.016 - sampleLogger - WARNING] <RootLogger root (INFO)>

# sample.log.1 文件
[2023-08-18 23:52:43.016 - sampleLogger - INFO] 10
1
2
3
4
5
6
7
8
9
10
11
解释：

log.yaml 中root定义了根日志器配置，在应用程序中通过logging.getLogger()获取根日志器（注意不需要传name），根日志器中如果不定义level、handlers等配置，将使用默认的WARNING、sys.stdout

在yaml或json配置文件中需要引用配置以外的对象时，如：sys.stdout，则需要加上ext://前缀， 配置系统会将ext:// 去除，而该值的剩余部分将使用正常导入机制来处理。

另外需要注意的是，由于YAML语法的原因，标量中不能出现一些特殊字符开头，如：%、[、{等，这些字符在YAML语法中都有特殊含义（如下图），因此如果必须出现，在标量开头，请用单引号括起来（单引号括起来的所有字符都是字面字符，双引号括起来的可以接收转义字符）


fileHandler处理器的配置使用了RotatingFileHandler类，支持文件按大小进行轮转。从输出结果来看，发生日志轮转时，不会将一条日志切割分到两个日志文件中去。如示例中，设置的maxBytes: 80，而[2023-08-18 23:52:43.016 - sampleLogger - INFO] 10共50个字符，[2023-08-18 23:52:43.016 - sampleLogger - WARNING] <RootLogger root (INFO)>共75个字符，后者并没有被分割为30、45个字符分别放到两个文件中。另外，即使写入1条日志时长度超过设置的maxBytes，该条日志也不会被分割到两个文件中去。

另外，logging.config.dictConfig() 还支持Filters过滤器配置，而logging.config.fileConfig()不能支持过滤器配置。上述示例中未给出Filters配置，有空再单独总结关于logging.config.dictConfig()配置Filters的用法吧。

拜了个拜~

参考资料：logging.config — 日志记录配置

