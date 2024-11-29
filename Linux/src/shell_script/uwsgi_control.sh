#!/bin/bash

# 虚拟环境路径
VENV_PATH="/root/dj-env/bin/activate"
# uwsgi 配置文件
UWSGI_INI="/ITAM/uwsgi.ini"
# uwsgi pid 文件路径，确保与你的配置文件中的 pidfile 对应
UWSGI_PID="/ITAM/uwsgi.pid"

# 启动 uwsgi
start() {
    echo "Activating virtual environment..."
    source $VENV_PATH
    echo "Starting uwsgi..."
    uwsgi --ini $UWSGI_INI
    echo "uwsgi started."
}

# 停止 uwsgi
stop() {
    if [ -f "$UWSGI_PID" ]; then
        echo "Stopping uwsgi..."
        kill -9 $(cat $UWSGI_PID)
        rm -f $UWSGI_PID
        echo "uwsgi stopped."
    else
        echo "uwsgi is not running or pid file not found."
    fi
}

# 重启 uwsgi
restart() {
    echo "Restarting uwsgi..."
    stop
    start
    echo "uwsgi restarted."
}

# 检查 uwsgi 状态
status() {
    if [ -f "$UWSGI_PID" ]; then
        PID=$(cat $UWSGI_PID)
        if ps -p $PID > /dev/null; then
            echo "uwsgi is running with PID $PID."
        else
            echo "uwsgi pid file exists but the process is not running."
        fi
    else
        echo "uwsgi is not running."
    fi
}

# 检查输入的命令并执行相应的操作
case "$1" in
    start)
        start
        ;;
    stop)
        stop
        ;;
    restart)
        restart
        ;;
    status)
	status
	;;
    *)
        echo "Usage: $0 {start|stop|restart|status}"
        exit 1
        ;;
esac

