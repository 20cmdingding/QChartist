<?php
// HTML code
// (replace (questionmark) with ?)

include("page_begin_login.php");
?>

<div align="left"><img src="images/main.jpg" width="440" height="162"></div>

<?php
if (isset($alert)) print $alert; ?>
<h1>Login</h1>
<script language="JavaScript" type="text/javascript">
<!--
// converted using http://accessify.com/tools-and-wizards/developer-tools/html-javascript-convertor/
function writeJS(){
var str='';
str+='<form name="login" action="" method="post" onsubmit="javascript:doLogin(this);">';
str+='	<table align="left" border="0" cellspacing="0" cellpadding="3">';
str+='		<tr>';
str+='			<td>Username:<\/td>';
str+='			<td><input type="text" name="user" value="<?php printField('user'); ?>" maxlength="30"><\/td><\/tr>';
str+='		<tr>';
str+='			<td>Password:<\/td>';
str+='			<td><input type="password" name="pass_field"><\/td><\/tr>';
str+='		<tr>';
str+='		<tr>';
str+='			<td colspan="2" align="left">';
str+='				<input type="checkbox" name="remember">';
str+='				<font size="2">Remember me next time<\/font>';
str+='			<\/td>';
str+='		<\/tr>';
str+='		<tr>';
str+='			<td colspan="2" align="right">';
str+='				<input type="hidden" name="pass" value="" \/>';
str+='				<input type="hidden" name="salt" value="<?php print $salt; ?>" \/>';
str+='				<input type="hidden" name="key" value="<?php print $_SESSION['key']; ?>" \/>';
str+='				<input type="submit" name="subform" value="Login">';
str+='			<\/td>';
str+='		<\/tr>';
<?php
if (ALLOW_JOIN) {
?>
str+='		<tr>';
str+='			<td colspan="2" align="left"><a href="register.php">Join<\/a><\/td>';
str+='		<\/tr>';
<?php
}

if (ALLOW_RESET) {
?>
str+='		<tr>';
str+='			<td colspan="2" align="left"><a href="forgot.php">Forgot password<\/a><\/td>';
str+='		<\/tr>';
<?php
}
?>
str+='	<\/table>';
str+='<\/form>';
document.write(str);
}
//writeJS();
//-->
</script>
<?php //<noscript>You need Javascript to use this page.</noscript> ?>
<form name="login" action="" method="post" onsubmit="javascript:doLogin(this);">
	<table align="left" border="0" cellspacing="0" cellpadding="3">
	<tr>
		<td>Username:</td>
		<td><input type="text" name="user" value="<?php printField('user'); ?>" maxlength="30"></td></tr>
	<tr>
		<td>Password:</td>
		<td><input type="password" name="pass_field"></td></tr>
	<tr>
	<tr>
		<td colspan="2" align="left">
			<input type="checkbox" name="remember">
			<font size="2">Remember me next time</font>
		</td>
	</tr>
	<tr>
		<td colspan="2" align="right">
			<input type="hidden" name="pass" value="" />
			<input type="hidden" name="salt" value="<?php print $salt; ?>" />
			<input type="hidden" name="key" value="<?php print $_SESSION['key']; ?>" />
			<input type="submit" name="subform" value="Login">
		</td>
	</tr>
<?php
if (ALLOW_JOIN) {
echo '
	<tr>
		<td colspan="2" align="left"><a href="register.php?ref='.$ref.'">Join</a></td>
	</tr>
';
}
?>
<?php
if (ALLOW_RESET) {
echo '
	<tr>
		<td colspan="2" align="left"><a href="forgot.php?ref='.$ref.'">Forgot password</a></td>
	</tr>
';
}
?>
</table>
</form>
<?php
include ("page_end.php");
?>