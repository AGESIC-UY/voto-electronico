         ____                                      
        / __/________  ___        ____ _____ _   __
       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ / 
     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
                               /____/              

DOCUMENTATION: HOW TO INSTALL CUSTOM PHP.INI IN SOME SHARED ENVIRONMENTS

FREE-GOV installation may require custom php.ini for PHP configuration.
This way, we avoid repeated calling to run-time functions to change
properties that should be configured just once at installation time.

In a dedicated server, php.ini modification is straightforward. But
a virtual domain environment may be tricky...
Here are some tricks. Enjoy!


>> EXAMPLE CUSTOM PHP.INI ON A SHARED ENVIRONMENT

Create "cgi-bin" folder in the virtual directory of working domain  
Inside cgi-bin folder: 
1) cp /etc/php5/cgi/php.ini .
2) nano php-wrapper.fcgi
    #!/bin/sh
    export PHPRC=/home/yourusername/example.com/cgi-bin
    exec /dh/cgi-system/php5.cgi $*

3) permisions:
chmod 755 cgi-bin
chmod 755 cgi-bin/php-wrapper.fcgi
chmod 640 cgi-bin/php.ini

4) .htaccess
Options +ExecCGI
AddHandler php5-cgi .php
Action php-cgi /cgi-bin/php-wrapper.fcgi
Action php5-cgi /cgi-bin/php-wrapper.fcgi 
