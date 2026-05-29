循环控制语句:

for name [ in word ] ; do list ; done
for (( expr1 ; expr2 ; expr3 )) ; do list ; done
for loop in `cat file`
   do echo $loop
   done

select name [ in word ] ; do list ; done
case word in [ [(] pattern [ | pattern ] ... ) list ;; ] ... esac
if list; then list; [ elif list; then list; ] ... [ else list; ] fi
if [ "10" -lt "12" ]
then 
elif
 then 
 else
fi 
while list; do list; done
until list; do list; done
[ function ] name () { list; }

expr 用来计算表达式的值
 
test 
  [ "a" == "string" ]
  [ "a" != "string" ]
  [ -z "a" ] 空值
  [ -n "a" ] 不为空值为真

  [ $x -eq 1 ] 
  [ $x -ne 1 ]
  [ $x -lt 1 ]
  [ $x -gt 1 ]
  [ $x -le 1 ]
  [ $x -ge 1 ]
  [ -d $file ]
  [ -f $file ]
  [ -s $file ]
  [ -r $file ]
  [ -w $file ]
  [ -x $file ]

  [ $a -a $b ]
  [ $a -o $b ]
  [ !$a ]
