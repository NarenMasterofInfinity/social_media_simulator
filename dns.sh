server1="8.8.8.8"
server2="8.8.4.4"
$(echo $server1 >> sudo /etc/resolv.conf && echo $server2 >> sudo /etc/resolv.conf)
