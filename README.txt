         ____                                      
        / __/________  ___        ____ _____ _   __
       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ / 
     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
                               /____/              

    SISTEMA DE VOTO ELECTRONICO, CREADO EN EL MUNICIPIO DE MALDONADO,
    SOBRE LA PLATAFORMA DE GOBIERNO ELECTRONICO FREE-GOV (LICENCIA AGPL)
                               
    #
    #  ESTE INSTRUCTIVO HA SIDO APORTADO POR EL MUNICIPIO DE MALDONADO
    #  http://www.municipiomaldonado.gub.uy/voto_electronico
    #
    #  Programador:      Iris Montes de Oca (iris@municipiomaldonado.gub.uy)
    #  Autor del Manual: Iris Montes de Oca
    #

    #  Versi�n del manual: 1.0 (1/4/2016) 
    
    
    SISTEMA DE VOTO ELECTRONICO

    CONTENIDO DEL MANUAL

      1) Paradigma de funcionamiento (�donde est� index.php?)
      2) Requisitos del Sistema
      3) Precauciones de Seguridad
         3.1) Mover carpetas de sistema fuera de ra�z httpd
         3.2) HTTPS (conexi�n cifrada)
         3.3) Borrado de archivos post-instalaci�n
         3.4) Permisos restringidos del usuario SQL
         3.5) Otras consideraciones de seguridad
      4) Instalaci�n
         4.1) Base de datos
         4.2) Configuraci�n del archivo .configuration
         4.3) Personalizaci�n de im�genes y logos
         4.4) php.ini personalizado
      5) Creaci�n inicial de usuarios y passwords
      6) Instalaci�n como m�dulo en una plataforma Free-gov preexistente
         6.1) Copia del m�dulo
         6.2) Archivo de aterrizaje
         6.3) Creaci�n del grupo y los permisos ACL
         6.4) Concepto de m�dulo en el contexto de una plataforma e-gov modular
      7) Fundamentos de uso del sistema
         7.1) Subsistema de administraci�n de la elecci�n  
             7.1.1) Series habilitadas
             7.1.2) Gestionar listas
             7.1.3) Gestionar circuitos
             7.1.4) Gestionar funcionarios
         7.2) Subsistema receptor de votos (mesa de votaci�n)
         7.3) Asignaci�n de votos a circuitos y auditor�a de responsabilidades
      8) Registros de actividad (logfiles)  
      9) Licencia del Software
     10) Por qu� se eligi� PHP como lenguaje para el desarrollo de este sistema


----------------------------------------------------------------------------------


1) PARADIGMA DE FUNCIONAMIENTO (�DONDE ESTA INDEX.PHP?)

En una instalaci�n de Free-gov no existe el archivo "index.php", de uso extendido
en ese lenguaje de programaci�n. En su lugar est� el archivo "front-controller.php"
Pero "front-controller.php" es m�s que un "index.php" renombrado: gracias a las
instrucciones en el archivo ".htaccess" (l�neas 53-57), este archivo recibe todas
las peticiones al servidor, a excepci�n  de peticiones a archivos presentes en el
filesystem (como im�genes, CSSs, javascripts, etc).
De este modo, un mismo archivo procesa TODAS las pantallas que generar� el sistema,
y las carpetas/archivos a los que se accede en las URIs no son reales, sino que son
parametros que recibe "front-controller.php" para su operaci�n.



2) REQUISITOS DEL SISTEMA

Para instalar 'Voto Electr�nico' es necesario contar con:
 - Cualquier sistema operativo para servidores (Linux, FreeBSD, Solaris, etc.)
 - Servidor Apache configurado con mod_rewrite y para usar archivos .htaccess
 - HTTPS + OpenSSL operativo (configuraci�n de SSL y certificado X.509 v�lido)
 - PHP version 5.2 o posterior con extensiones mysqli y gdlib
 - MySQL 5 o posterior
 - Un subdominio disponible en exclusividad para la instalaci�n
 - Se recomienda disponer de la herramienta phpMyAdmin

Tenga presente que la instalaci�n de la plataforma Free-gov modifica profundamente
el funcionamiento del servidor Apache en su subdominio. Por tanto es imposible 
hacer que este sistema coexista con alguna p�gina web normal poni�ndolo dentro de 
un directorio. Se debe disponer de un subdominio o dominio virtual con una 
estructura propia de directorios:

      http://www.sitioweb.gov/voto  >>  Incorrecto (da errores graves)
      http://voto.sitioweb.gov      >>  Correcto

PHP puede funcionar enlazado al servidor web Apache mediante mod_php, aunque se
recomienda la interfaz 'fastcgi', de mucho mejor performance.

No es necesario instalar previamente la plataforma de Gobierno Electr�nico
Free-gov, ya que la misma est� inclu�da y preconfigurada en esta distribuci�n del
software. Si ya se dispone de una plataforma Free-gov, se puede agregar el m�dulo
'Voto Electr�nico' siguiendo las indicaciones del punto 5 en este mismo manual.

Como �ltima precauci�n es oportuno aclarar que el proyecto contiene varios 
archivos ocultos (que comienzan con el caracter '.'). Muchos programas de FTP no
pueden ver o copiar estos archivos a menos que se les active la opci�n "mostrar
archivos ocultos".



3) PRECAUCIONES DE SEGURIDAD

3.1 - Se recomienda mover las carpetas "free-gov-core" y "modules" a cualquier 
lugar del filesystem del servidor, fuera de la carpeta ra�z del httpd. En ese 
caso, modifique las l�neas 42 y 43 del archivo "front-controller.php", para indicar 
la nueva ruta a "CORE_PATH" y "MODULES_PATH" (las carpetas de n�cleo y m�dulos).

3.2 - Este software est� configurado por defecto para forzar al servidor web a
usar HTTPS en lugar de HTTP: cuando un usuario accede a http://www.voto.gub, el
sistema reescribe la petici�n usando una conexi�n segura: https://www.voto.gub.
Si para probar el sistema no se desea usar HTTPS, deshabilite este comportamiento
comentando las l�neas 45 y 46 del archivo .htaccess en la ra�z de la aplicaci�n.
Adicionalmente, deber� cambiar en las l�neas 66 y 67 del archivo front_controller.php 
donde dice 'cookie_secure'=>TRUE a 'cookie_secure'=>FALSE. Tenga presente que al
eliminar la conexi�n segura (y todos los recaudos que el sistema toma al respecto)
se estar� haciendo una instalaci�n no apta para uso profesional en e-government.

3.3 - Una vez terminada su intalaci�n, tenga la precauci�n de borrar del servidor 
los archivos de documentaci�n (VERSION.txt, README.txt, etc.) as� como el archivo 
.sql que se suministra para inicializar la base de datos.

3.4 - Es conveniente que su servidor MySQL tenga dos usuarios con acceso a su base
de datos. Un usuario con amplios permisos, que ser� usado durante la instalaci�n 
para crear las tablas y configurar los usuarios iniciales del sistema; y un usuario
SQL con permisos restringidos a las operaciones de SQL: SELECT, INSERT, UPDATE, DELETE
e INDEX. Tambi�n tenga presente configurar el ACL del MySQL para que el usuario 
operativo s�lo pueda acceder desde la IP de su servidor; preferentemente una IP de red 
privada  en una segunda interfaz ethernet configurada para su backend (proveyendo la 
conexi�n httpd-sql en una red segura y sin interferir con el tr�fico http leg�timo).

3.5 - Si s�lo va a probar este software, cualquier instalaci�n LAMP o WAMP moderna 
es suficiente. Puede instalar f�cilmente todo el software necesario desde
un paquete como XAMPP (http://sourceforge.net/projects/xampp/), que preinstala
Apache, Mysql, PHP, etc. de forma unificada y sin esfuerzo.
Pero una implementaci�n de Gobierno Electr�nico seria requiere un cortafuegos,
una auditor�a de seguridad permanente con honeypots y detecci�n de intrusiones, 
una pol�tica de respaldos diarios, de replicaci�n de bases de datos, un entorno
chroot, un proxy saliente, etc.
La plataforma de gobierno electr�nico 'Free-gov' sobre la que se basa este sistema
es totalmente segura en la medida que sea manejada por administradores de sistemas
competentes y concientes de que deben complementar toda instalaci�n con las
diferentes herramientas de seguridad y respaldos disponibles para su sistema
operativo.
Como dice la documentaci�n de 'Free-gov': "la seguridad de una implementaci�n de
gobierno electr�nico es directamente proporcional a la solidez profesional de
su administrador de sistemas"



4) INSTALACION

4.1 - Base de datos - Es necesario crear una serie de tablas en una base de datos 
MySQL. Estas tablas contienen la estructura ACL (permisos de acceso y usuarios),
as� como las definiciones del m�dulo 'Voto Electr�nico'.
Para automatizar la creaci�n inicial de las tablas, se suministra un archivo de
nombre 'voto-electronico.sql' en la ra�z del proyecto.
Use el archivo 'voto-electronico.sql' desde su herramienta de gesti�n de 
MySQL (phpMyAdmin por ejemplo), ejecute las instrucciones SQL del archivo y se
crear�n autom�ticamente las estructuras de datos necesarias, adem�s de ciertas
configuraciones iniciales preestablecidas, y datos de ejemplo, que usted puede 
borrar (usuarios, series de credencial, listas de votaci�n).


4.2 - Configuraci�n del archivo .configuration - Este es el archivo principal de 
configurai�n del sistema, y se encuentra en la carpeta 'free-gov-core'. Si est� 
en una plataforma UNIX (como Linux o FreeBSD) tenga presente que es un archivo 
oculto, y  configure su gestor de archivos y su cliente FTP para mostrar archivos
ocultos. Dentro de .configuration usted deber� configurar la URI del servidor 
MySQL (si el MySQL est� en el mismo servidor web, ponga "loclhost", en caso 
contrario ponga el nombre o direcci�n IP del servidor de bases de datos). Tambi�n
deber� poner el nombre de la base de datos a usar, el nombre de usuario y password 
de MySQL. Dentro de '.configuration' se puede configurar el texto que se ver� en 
el t�tulo y en  el pie de cada p�gina. Por �ltimo, la configuraci�n de correo 
electr�nico no es requerida en la instalaci�n de 'Voto Electr�nico'


4.3 - Personalizaci�n de im�genes y logos - En la carpeta 'http-root/images' hay 
una imagen de nombre 'topbanner-trans.png' que es la que aparece en la portada del
Panl de Administraci�n. Puede ser sustitu�da por otra imagen PNG de las mismas
dimensiones y con el mismo nombre.
Tambi�n hay un logotipo del municipio 'logomunicipio1.png'. Puede borrarlo y poner 
un logotipo personalizado, en el mismo entorno de dimensiones. 


4.4 - php.ini personalizado - La plataforma 'Free-gov' usa una configuraci�n de 
PHP especial y optimizada (aunque no es un requerimiento forzoso). Si usted tiene
la posibilidad de manipular el php.ini global del servidor, use el archivo 
'php.ini' que se suministra dentro de la carpeta 'cgi-bin' del proyecto. 
Si no puede cambiar la configuraci�n global de PHP, entonces siga las instrucciones 
del archivo README.txt suministrado en la carpeta 'cgi-bin'. Luego descomente las 
siguientes l�neas, que son las primeras instrucciones del archivo .htaccess en la 
ra�z de la instalaci�n ("descomentar" o "quitar el comentario" es borrar el 
caracter # que precede la l�nea):

    #Options +ExecCGI
    #AddHandler php5-cgi .php
    #Action php-cgi /cgi-bin/php-wrapper.fcgi
    #Action php5-cgi /cgi-bin/php-wrapper.fcgi
    
La configuraci�n del php.ini personalizado indicada en este paso no es forzosa, 
pero es clave para un uso m�s profesional de la plataforma de Gobierno Electr�nico 
Free-gov (hay sistemas que en cada petici�n al front-controller establecen 
variables como zona horaria, nombre de las cookies por defecto, etc. El proyecto
Free-gov entiende que estos valores se deber�an establecer s�lo una vez durante
la instalaci�n, aligerando el trabajo de CPU de cada petici�n, lo cual es muy
importante en servidores sujetos a mucha carga).



5) CREACION INICIAL DE USUARIOS Y PASSWORDS

Los usuarios (funcionarios que tendr�n acceso al sistema con diferentes privilegios)
se crean en la base de datos, en la tabla 'acl_users'.
Existe un  usuario inicial, de nombre 'usuarioinicial' y cuyo password es 
'cambiarurgente'. Este usuario fue creado en la l�nea 117 del archivo 
'voto-electronico.sql':

INSERT INTO `acl_users` (`id`, `username`, `cryptpass`, `realname`) VALUES
(1, 'usuarioinicial', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Usuario');

Como se puede ver, en la base de datos no se guardan los passwords, sino una firma
hash (MD5 + SHA2) del mismo, que por razones de seguridad es irreversible.
Al crear un usuario nuevo, se hace desde el administrador de la base de datos (que
puede ser phpMyAdmin, por ejemplo). A cada usuario que se ingrese, se le puede 
poner en el campo de password la cadena 7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6 
entonces ese usuario tendr� como password la cadena 'cambiarurgente'. El usuario 
deber� ingresar a su cuenta inmediatamente y cambiar el password por uno de su
preferencia, el que a su vez se guardar� encriptado. Si un usuario olvida su 
password, el administrador lo podr� resetear volviendo a poner la cadena 
7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6 para que el usuario acceda por �nica vez
con el password 'cambiarurgente'.

Luego de creados cada usuario, es necesario manipular una segunda tabla del ACL 
(Access Control List) para hacer que estos usuarios pertenezcan al grupo 
'elecciones_admin'. Esto se hace en la tabla 'acl_users2groups'. Cada usuario 
-una vez ingresado a la tabla 'acl_users'- tiene un n�mero de ID autoincremental 
asociado. En la tabla 'acl_users2groups' simplemente hay dos campos ('user' y 
'group'), y la llenamos poniendo entradas con el ID de cada usuario, y la cadena 
de grupo 'elecciones_admin'.  Para ilustrar lo explicado, abajo se muestra la 
l�nea del archivo 'voto-electronico.sql' que establece los permisos del usuario 
'usuarioinicial' (cuyo id es '1'):

  INSERT INTO `acl_users2groups` (`user`, `group`) VALUES
  (1, 'elecciones_admin'),
  (1, 'elecciones_mesa');
  
En el ejemplo precedente, estamos haciendo que el usuario "1" pertenezca tanto
al grupo 'elecciones_admin' (administraci�n del sistema) como al segundo grupo 
'elecciones_mesa' (miembros de mesa receptora de votos). Por tanto, este usuario
tendr� en su men� un acceso a todas las pantallas (votaci�n, configutaci�n, etc).

Si creamos un usuario pero olvidamos darle pertenencia por lo menos a un grupo,
cuando este usuario ingrese al sistema ver� un mensaje de error indicando que
no pertenece a ning�n grupo y que no tiene permisos para nada (Free-gov usa una
pol�tica de seguridad de restricci�n por defecto apta para Gobierno Electr�nico).
  
  
  
6) INSTALACION COMO MODULO EN UNA PLATAFORMA FREE-GOV PREEXISTENTE 
 
Si su organismo ya dispone de una instalaci�n de la plataforma de Gobierno 
Electr�nico Free-gov, entonces considere integrar el Sistema 'Voto Electr�nico'
como m�dulo de su instalaci�n existente.
De esa forma, los usuarios de 'Voto Electr�nico' ver�n aparecer los comandos
de este software en el men� de su pantalla habitual de Free-gov, y a la vez �ste
seguir� inaccesible para los usuarios que no hayan sido expl�citamente agregados
al grupo de administradores o al de receptores de 'Voto Electr�nico'.

6.1 - Copia del m�dulo - en la carpeta 'modules' de su instalaci�n existente de
Free-gov copie la carpeta 'elecciones' que se halla dentro de la carpeta 'modules'
de esta distribuci�n.

6.2 - Archivo de aterrizaje - Para aquellos funcionarios que tengan acceso a otras 
funciones de su instalaci�n Free-gov, el funcionamiento del sistema no presentar�
cambios. Pero los funcionarios que s�lo pertenezcan al grupo 'elecciones_admin'
necesitar�n una pantalla "de aterrizaje" donde ingresar cuando entren al sistema.
El aterrizaje de 'Voto Electr�nico' es el archivo 'elecciones_admin.inc' que 
se halla dentro de las carpetas 'modules/main' Debe copiarlo en la ruta 
'modules/main' de su instalaci�n de Free-gov existente.

6.3 - Creaci�n del grupo y los permisos ACL - Desde el gestor de MySQL (phpMyAdmin)
cree el grupo 'elecciones_admin' en la tabla de grupos 'acl_groups':

  INSERT INTO `acl_groups` (`name`, `description`) VALUES
  ('elecciones_admin', 'Gestiona sistema Voto Electronico'),
  ('elecciones_mesa',  'Funcionario receptor de votos');

Ahora debe crear el "mapa" que vincula al grupo con las diferentes operaciones 
permitidas, as� como los elementos del men� que se crear�n cuando corresponda.
Esto se realiza en la tabla 'acl_groups2res' que mapea los grupos a los recursos a
ser accesados, agregando las reglas para el grupo 'elecciones_admin'. Ejecute la 
siguiente instrucci�n SQL:

   INSERT INTO `acl_groups2res` (`id`, `group`, `module`, `operation`, `negative`, 
   `menu_group`, `menu_caption`) VALUES
   (12, 'elecciones_admin', 'elecciones', 'index', 0, NULL, NULL),
   (13, 'elecciones_admin', 'elecciones', 'serieshab', 0, 'Configuraci�n acto 
         eleccionario', 'Series habilitadas'),
   (14, 'elecciones_admin', 'elecciones', 'serieshab_c', 0, NULL, NULL),
   (15, 'elecciones_admin', 'elecciones', 'serieshab_d', 0, NULL, NULL),
   (16, 'elecciones_admin', 'elecciones', 'listas', 0, 'Configuraci�n acto 
         eleccionario', 'Gestionar Listas'),
   (17, 'elecciones_admin', 'elecciones', 'listas_c', 0, NULL, NULL),
   (18, 'elecciones_admin', 'elecciones', 'listas_d', 0, NULL, NULL),
   (19, 'elecciones_mesa', 'elecciones', 'votosmesa', 0, 'Acto eleccionario', 
        'Votos emitidos'),
   (20, 'elecciones_mesa', 'elecciones', 'votar', 0, 'Acto eleccionario', 
        'Emitir Voto'),
   (21, 'elecciones_mesa', 'elecciones', 'votar2', 0, NULL, NULL),
   (22, 'elecciones_admin', 'elecciones', 'circuitos', 0, 'Configuraci�n acto 
         eleccionario', 'Gestionar Circuitos'),
   (23, 'elecciones_admin', 'elecciones', 'circuitos_c', 0, NULL, NULL),
   (24, 'elecciones_admin', 'elecciones', 'circuitos_d', 0, NULL, NULL),
   (25, 'elecciones_admin', 'elecciones', 'funcionarios', 0, 'Configuraci�n 
         acto eleccionario', 'Gestionar funcionarios'),
   (26, 'elecciones_admin', 'elecciones', 'funcionarios_c', 0, NULL, NULL),
   (27, 'elecciones_admin', 'elecciones', 'funcionarios_d', 0, NULL, NULL),
   (28, 'elecciones_admin', 'elecciones', 'escrutinio', 0, 'Acto eleccionario', 
        'Escrutinio Global'),
   (29, 'elecciones_admin', 'elecciones', 'escrutiniocircuito', 0, 'Acto 
         eleccionario', 'Escrutinio Circuital'),
   (30, 'elecciones_mesa', 'elecciones', 'votosmesa_p', 0, NULL, NULL);
   

Por �ltimo agregue los usuarios que corresponda al grupo 'elecciones_admin', 
de esta forma no s�lo tendr�n acceso al m�dulo 'Voto Electr�nico' sino que
adem�s aparecer�n los enlaces a las diferentes herramientas en el men� del
sistema del usuario. Un ejemplo de c�mo agregar los usuarios con IDs 1, 5 y 100:

  INSERT INTO `acl_users2groups` (`user`, `group`) VALUES
  (1, 'elecciones_admin'),
  (1, 'elecciones_mesa'),
  (5, 'elecciones_admin'),
  (5, 'elecciones_mesa'),  
  (100, 'elecciones_admin');

  
6.4 - Concepto de m�dulo en el contexto de una plataforma e-gov modular - Free-gov 
fue concebido para permitir que en una misma instalaci�n coexistan una cantidad 
de m�dulos diversos, permitiendo a cada usuario ver s�lo aquellos que 
corresponden a su tarea, y simplificando la tarea de usuarios que requieren el
uso de varias herramientas al centralizarlas todas bajo un mismo proceso de login.
En la URI de un usuario logueado en panel de control podemos ver:
    https://www.sitio.gov/MODULO/OPERACION/PARAMETRO1/PARAMETRO2/PARAMETROn

En nuestro caso MODULO es 'elecciones', mientras OPERACION puede ser por ejemplo 
'circuitos_c', que es la pantalla desde donde se da de alta (create) un circuito.    



7) FUNDAMENTOS DE USO DEL SISTEMA

'Voto Electr�nico' es un sistema con un subsistema de acceso privado (donde
los funcionarios configuran y mantienen los par�metros de un acto electoral) y
un subsistema semi-p�blico (donde los funcionarios receptores de votos ingresan
los datos de los votantes, quienes luego eligen a solas, desde una pantalla
creada para el elector).
 
7.1 - Subsistema de administraci�n de la elecci�n  
Es un Panel de Control donde s�lo acceden los funcionarios autorizados. Desde el 
Panel de Control se administra una base de  datos de elementos como Listas, 
Circuitos, Funcionarios receptores de votos, etc.
Tambi�n es posible realizar escrutinios finales o parciales, globales o a nivel
de circuito.

    7.1.1 - Series habilitadas - Desde esta herramienta se mantiene la lista de
            Series de Credencial C�vica habilitadas para el acto eleccionario.
            En nuestra configuraci�n, el acto eleccionario es de alcance municipal,
            por lo tanto s'olo se deja votar a vecinos del municipio (esta carac-
            ter�stica puede ser reprogramada en caso de realizzarse una elecci�n
            de otro alcance).
    7.1.2 - Gestionar listas - Desde esta herramienta, el administrador da de alta
            las listas que participar�n en el acto eleccionario.
    7.1.3 - Gestionar circuitos - Desde esta herramienta, el administrador maneja
            los circuitos de recepci�n de votos. Es importante completar la carga 
            de circuitos antes de proceder a dar de alta los funcionarios receptores
            de votos, ya que el alta de los mismos requere la asociaci�n a un 
            circuito espec�fico.
    7.1.4 - Gestionar funcionarios - Desde esta herramienta se dan de alta los 
            funcionarios que trabajar�n en las mesas receptoras de votos. Cada
            funcionario est� vinculado a un circuito (o mesa receptora), y los votos
            gestionados por el funcionario se asignar�n a su circuito vinculado. Por 
            eso es importante mantener esta informaci�n actualizada cuando un 
            funcionario es reasignado a otro circuito.

7.2 - Subsistema receptor de votos (mesa de votaci�n)
Es el conjunto de pantallas desde donde los funcionarios receptores de votos
ingresan los datos de cada votante y validan que no haya votado a�n. 
Si todo es correcto, se despliega la pantalla del votante. En ese momento, el
funcionario se retira y el votante queda oculto tras la mampara suministrada por 
la Corte Electoral. El ciudadano elige su opci�n de voto y la confirma.
Una vez se haya votado, se retorna a una pantalla donde aparece el listado de
personas que votaron en la mesa. Si el votante aparece en el listado (como primer
elemento de la lista), entonces queda confirmado que el voto se emiti� de forma
exitosa. Desde ese listado se pueden imprimir los comprobantes de votaci�n (desde
el �cono de impresora a la derecha del rengl�n de registro del votante).
El subsistema de acceso p�blico procesa, valida y sanea su entrada a fin de evitar
ataques de tipo XSS o de inyecci�n SQL.


7.3 - Asignaci�n de votos a circuitos y auditor�a de responsabilidades
En este software, cada funcionario receptor de votos tiene su propio acceso al 
sistema, con su nombre de usuario y contrase�a. En una mesa receptora de votos,
el funcionario responsable de la PC en un determinado momento, debe estar al mando
de su propia sesi�n (en la pantalla aparece el nombre del funcionario responsable).
Cuando los funcionarios se alternen en el manejo de la PC, deben cerrar la sesi�n
y el nuevo funcionario debe iniciar sesi�n con sus datos. Se prohibe que un
funcionario est� trabajando en la sesi�n de otro funcionario. Adicionalmente, la
sesi�n se cierra autom�ticamente luego de 5 minutos de inactividad (al igual que
en la Banca Electr�nica).
Cada funcionario es responsable por la actividad que se lleva a cabo en su sesi�n
de trabajo.
El sistema contabiliza los votos para cada funcionario, a la vez que lleva el
control de los inicios y cierres de sesi�n, as� como de cualquier error que pudiera
surgir en las diferentes pantallas (n�meros de documento mal ingresados, intentos
de ingreso de campos vac�os, etc).
El eje del control del sistema es la sesi�n del funcionario. Como a su vez cada
funcionario est� asignado a un circuito, el software termina de componer los 
escrutinios por circuito sumando los votos ingresados por los funcionarios asignados.



8) REGISTROS DE ACTIVIDAD (LOGFILES)

Free-gov guarda los registros de actividad en la tabla 'log' de la base de datos.
All� registra toda la actividad que se realiza en el sistema: ingreso de usuarios,
cierres de sesi�n, errores, intentos de ataques, etc. Para cada registro guarda
d�a y hora detallada, caracter�sticas de la m�quina con la que se accede, datos
del uso de un posible servidor proxy (una t�cnica muy usada por atacantes), etc.
En el caso de ataques, el sistema encripta la cadena usada por el atacante y la
guarda en el registro, junto a la direcci�n IP del origen del ataque. Esto evita
ataques de tipo "inyecci�n SQL".

Con toda esa informaci�n a almacenar, la tabla 'log' puede crecer desmedidamente,
por lo que se recomenda pasar peri�dicamente los datos a un soporte paralelo para
fines de archivo, y vaciar la tabla para mantener el servidor SQL m�s libre. 



9) LICENCIA DEL SOFTWARE

La licencia es AGPL versi�n 3 (Affero General Public License), creada por la Free 
Software Foundation y reconocida por OSI (Open Source Initiative).
Este software se distribuye bajo la misma licencia de Software Libre que utiliza 
la Plataforma de Gobierno Electr�nico 'Free-gov' sobre la que fue desarrollado.
Este software se puede descargar, estudiar, modificar, instalar en cuantas PCs se
desee, se puede copiar, se puede dar a terceros con total libertad... la �nica
restricci�n que impone la licencia es que cuando Ud. copie el software y se lo
de a un tercero, lo haga acompa�ado del c�digo fuente del programa, y con las
mismas libertades con que Ud. lo recibi� (y bajo la misma licencia).
Una copia en ingl�s de la licencia acompa�a al proyecto en el archivo 'license.txt'
La licencia original en ingl�s es la que tiene valor legal en todo el mundo, y se
aplica de acuerdo al Derecho Internacional y los tratados internacionales sobre 
Derechos de Autor.

Puede leer m�s acerca de esta licencia en:
    http://es.wikipedia.org/wiki/GNU_Affero_General_Public_License

Puede acceder al texto oficial completo de la licencia AGPL en:
    http://www.gnu.org/licenses/agpl.html

Al momento de escribir este documento lamentablemente no exist�an traducciones al
espa�ol del texto de la licencia AGPL.



10) POR QUE SE ELIGIO PHP COMO LENGUAJE PARA EL DESARROLLO DE ESTE SISTEMA

La elecci�n de un lenguaje de programaci�n es un tema pasional que suele provocar
"guerras santas" entre los partidarios de una u otra tecnolog�a: es como la 
pertenencia a una religi�n, o como el ser hincha de un club deportivo.
Pero m�s all� de creencias ypasiones, la elecci�n de un lenguaje tiene que 
fundarse en ventajas reales y demostrables, adem�s de existir antecedentes del 
uso de esa tecnolog�a en sistemas de misi�n cr�tica de gran porte.

Compartimos las mismas razones que el proyecto Free-gov enumera en su sitio:

- PHP es Software Libre, y adem�s de ahorrar costos de licencias, su modelo de
desarrollo Open Source (con decenas de miles de programadores estudiando,
analizando y mejorando el producto) ha hecho de PHP la plataforma de desarrollo
para programaci�n web m�s s�lida y completa del mercado, superando con creces
a cualquier producto comercial.
- PHP act�a como un lenguaje interpretado, y sin embargo es posible compilar
los scripts para mejorar la velocidad de ejecuci�n (ejemplo: Facebook)
- PHP es el m�s popular de los lenguajes de programaci�n Server-Side, por lo
tanto es m�s sencillo hallar programadores calificados, colaboradores, etc. 
- PHP es multiplataforma y puede ser usado con cualquier sistema operativo, y
con cualquier servidor web. No estamos forzados a usar un sistema en particular
Existen instalaciones de PHP completamente usables funcionando 100% en la CPU
de tel�fonos celulares; en el otro extremo, existen compilaciones de PHP 
corriendo en mainframes, supercomputadoras y clusters PVM. Si tiene un celular
con Android, instale "Web Server Ultimate" o "Bit Web Server" y ponga a funcionar
"Voto Electr�nico" usando su celular como servidor.
- PHP es ampliamente usado en las empresas de hosting comercial, por tanto un
programa en PHP puede ser f�cilmente migrado a cualquier servidor externo, a�n
los de m�s bajo costo.
- PHP (cuando est� debidamente instalado y configurado) es una plataforma de
extrema seguridad, perfectamente apta para Gobierno Electr�nico, tal como lo
demuestra el proyecto Free-gov.
- PHP soporta programaci�n de alto y bajo nivel (tan bajo como sockets TCP/IP)
- PHP est� pre-empaquetado con Apache y MySQL por defecto en la mayor�a de las 
distribuciones Linux, as� como en FreeBSD, OpenBSD, Solaris, etc.
- PHP soporta tanto Programaci�n Orientata a Obejtos (OOP) como Programaci�n
Procedural Estructurada (esta �ltima es la preferida por Free-gov).

PHP es la tecnolog�a elegida por muchos de los sitios web m�s grandes del mundo:
Yahoo, Wikipedia, Facebook, Youtube, Flickr, Digg, y partes de Google.
PHP tambi�n es usado por aproximadamente el 82% de todos los servidores a nivel
mundial.

