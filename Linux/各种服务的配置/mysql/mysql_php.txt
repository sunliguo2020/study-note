新建PHP脚本

为了使工作简单化，我们仅仅编写2个脚本。其中一个将所有的数据库条目都以列表的形式显示出来；另外一个则允许我们增加新的内容。

index.php3

在你的Web目录（通常是Apache的htdocs 或者html目录）下新建一个叫example的目录：

# cd /home/httpd/htdocs
# mkdir example

接着，在此目录下用任意的文本编辑器编写一个叫index.php3的PHP3脚本，其内容至少是：

<html>
<head><title>Web Database Sample Index</title>
</head>
<body bgcolor=#ffffff>
<h1>Data from mytable</h1>

<?
mysql_connect("localhost", "webuser", "");
$query = "SELECT name, phone FROM mytable";
$result = mysql_db_query("example", $query);

if ($result) {
echo "Found these entries in the database:<ul>";
while ($r = mysql_fetch_array($result)) {
$name = $r["name"];
$phone = $r["phone"];
echo "<li>$name, $phone";
}
echo "</ul>";
} else {
echo "No data.";
}
mysql_free_result($result);
?>

<p><a href="add.php3">Add new entry</a>
</body>
</html>

　

add.php3

然后在同样目录下新编辑一个叫add.php3的脚本。此脚本完成两样事情：一：它会显示信息，提示用户向数据库添加数据；二：它会将输入的信息添加到数据库。

<html>
<head><title>Web Database Sample Inserting</title>
</head>

<body bgcolor=#ffffff>

<?
mysql_connect("localhost", "webuser", "");

if (isset($name) && isset($phone)) {
$query = "INSERT INTO mytable VALUES ('$name', '$phone')";
$result = mysql_db_query("example", $query);

if ($result) {
echo "<p>$name was added to the database</p>";
}
}
?>

<h1>Add an entry</h1>
<form>
Name: <input type=text name='name'><br>
Phone: <input type=text name='phone'><br>
<input type=submit>
</form>

<p><a href="index.php3">Back to index</a>
</body>
</html>

编写完简单又高效的脚本后，现在该测试它了。
测试
  mysqladmin ping
  mysqladmin version
  mysqlshow
