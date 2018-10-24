#1652238 田文睿
#!/bin/bash
if [ $# == 2 ]; then
    cat $1|grep -v "^ *#"|awk '$2>""{print $1,$2}' | while read line
    do
        useradd $(echo "u"$line|awk '{print $1}')
        echo '用户 '$(echo "u"$line|awk '{print $1}') $(echo "u"$line|awk '{print $2}')' 已添加！'
        echo $(cat $2) | passwd $(echo "u"$line|awk '{print $1}') --stdin > /dev/null 2>&1
        echo "passwd" > $2
        echo "已使用$2设置初始密码，首次登陆后请修改密码"
    done 
else
    echo "参数数量不为2，请检查"
fi