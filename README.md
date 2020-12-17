# Voto Electronico [DESCONTINUADO] 

Es un Software para actos electorales públicos, desarrollado y utilizado por el Municipio de Maldonado para la votación los proyectos del presupuesto participativo.

Entre sus características principales cuenta con un módulo para circuitos (mesas receptoras de Votos), escrutinio por mesa, escrutinio global, parametrización del acto eleccionario. 

Características técnicas:

Software para servidor arquitectura LAMP, sobre canales cifrados HTTPS (SSL2).

-----------------------------------------
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

    #  Versión del manual: 1.0 (1/4/2016) 
    
    
    SISTEMA DE VOTO ELECTRONICO

    CONTENIDO DEL MANUAL

      1) Paradigma de funcionamiento (¿donde está index.php?)
      2) Requisitos del Sistema
      3) Precauciones de Seguridad
         3.1) Mover carpetas de sistema fuera de raíz httpd
         3.2) HTTPS (conexión cifrada)
         3.3) Borrado de archivos post-instalación
         3.4) Permisos restringidos del usuario SQL
         3.5) Otras consideraciones de seguridad
      4) Instalación
         4.1) Base de datos
         4.2) Configuración del archivo .configuration
         4.3) Personalización de imágenes y logos
         4.4) php.ini personalizado
      5) Creación inicial de usuarios y passwords
      6) Instalación como módulo en una plataforma Free-gov preexistente
         6.1) Copia del módulo
         6.2) Archivo de aterrizaje
         6.3) Creación del grupo y los permisos ACL
         6.4) Concepto de módulo en el contexto de una plataforma e-gov modular
      7) Fundamentos de uso del sistema
         7.1) Subsistema de administración de la elección  
             7.1.1) Series habilitadas
             7.1.2) Gestionar listas
             7.1.3) Gestionar circuitos
             7.1.4) Gestionar funcionarios
         7.2) Subsistema receptor de votos (mesa de votación)
         7.3) Asignación de votos a circuitos y auditoría de responsabilidades
      8) Registros de actividad (logfiles)  
      9) Licencia del Software
     10) Por qué se eligió PHP como lenguaje para el desarrollo de este sistema


----------------------------------------------------------------------------------


1) PARADIGMA DE FUNCIONAMIENTO (¿DONDE ESTA INDEX.PHP?)

En una instalación de Free-gov no existe el archivo "index.php", de uso extendido
en ese lenguaje de programación. En su lugar está el archivo "front-controller.php"
Pero "front-controller.php" es más que un "index.php" renombrado: gracias a las
instrucciones en el archivo ".htaccess" (líneas 53-57), este archivo recibe todas
las peticiones al servidor, a excepción  de peticiones a archivos presentes en el
filesystem (como imágenes, CSSs, javascripts, etc).
De este modo, un mismo archivo procesa TODAS las pantallas que generará el sistema,
y las carpetas/archivos a los que se accede en las URIs no son reales, sino que son
parametros que recibe "front-controller.php" para su operación.



2) REQUISITOS DEL SISTEMA

Para instalar 'Voto Electrónico' es necesario contar con:
 - Cualquier sistema operativo para servidores (Linux, FreeBSD, Solaris, etc.)
 - Servidor Apache configurado con mod_rewrite y para usar archivos .htaccess
 - HTTPS + OpenSSL operativo (configuración de SSL y certificado X.509 válido)
 - PHP version 5.2 o posterior con extensiones mysqli y gdlib
 - MySQL 5 o posterior
 - Un subdominio disponible en exclusividad para la instalación
 - Se recomienda disponer de la herramienta phpMyAdmin

Tenga presente que la instalación de la plataforma Free-gov modifica profundamente
el funcionamiento del servidor Apache en su subdominio. Por tanto es imposible 
hacer que este sistema coexista con alguna página web normal poniéndolo dentro de 
un directorio. Se debe disponer de un subdominio o dominio virtual con una 
estructura propia de directorios:

      http://www.sitioweb.gov/voto  >>  Incorrecto (da errores graves)
      http://voto.sitioweb.gov      >>  Correcto

PHP puede funcionar enlazado al servidor web Apache mediante mod_php, aunque se
recomienda la interfaz 'fastcgi', de mucho mejor performance.

No es necesario instalar previamente la plataforma de Gobierno Electrónico
Free-gov, ya que la misma está incluída y preconfigurada en esta distribución del
software. Si ya se dispone de una plataforma Free-gov, se puede agregar el módulo
'Voto Electrónico' siguiendo las indicaciones del punto 5 en este mismo manual.

Como última precaución es oportuno aclarar que el proyecto contiene varios 
archivos ocultos (que comienzan con el caracter '.'). Muchos programas de FTP no
pueden ver o copiar estos archivos a menos que se les active la opción "mostrar
archivos ocultos".



3) PRECAUCIONES DE SEGURIDAD

3.1 - Se recomienda mover las carpetas "free-gov-core" y "modules" a cualquier 
lugar del filesystem del servidor, fuera de la carpeta raíz del httpd. En ese 
caso, modifique las líneas 42 y 43 del archivo "front-controller.php", para indicar 
la nueva ruta a "CORE_PATH" y "MODULES_PATH" (las carpetas de núcleo y módulos).

3.2 - Este software está configurado por defecto para forzar al servidor web a
usar HTTPS en lugar de HTTP: cuando un usuario accede a http://www.voto.gub, el
sistema reescribe la petición usando una conexión segura: https://www.voto.gub.
Si para probar el sistema no se desea usar HTTPS, deshabilite este comportamiento
comentando las líneas 45 y 46 del archivo .htaccess en la raíz de la aplicación.
Adicionalmente, deberá cambiar en las líneas 66 y 67 del archivo front_controller.php 
donde dice 'cookie_secure'=>TRUE a 'cookie_secure'=>FALSE. Tenga presente que al
eliminar la conexión segura (y todos los recaudos que el sistema toma al respecto)
se estará haciendo una instalación no apta para uso profesional en e-government.

3.3 - Una vez terminada su intalación, tenga la precaución de borrar del servidor 
los archivos de documentación (VERSION.txt, README.txt, etc.) así como el archivo 
.sql que se suministra para inicializar la base de datos.

3.4 - Es conveniente que su servidor MySQL tenga dos usuarios con acceso a su base
de datos. Un usuario con amplios permisos, que será usado durante la instalación 
para crear las tablas y configurar los usuarios iniciales del sistema; y un usuario
SQL con permisos restringidos a las operaciones de SQL: SELECT, INSERT, UPDATE, DELETE
e INDEX. También tenga presente configurar el ACL del MySQL para que el usuario 
operativo sólo pueda acceder desde la IP de su servidor; preferentemente una IP de red 
privada  en una segunda interfaz ethernet configurada para su backend (proveyendo la 
conexión httpd-sql en una red segura y sin interferir con el tráfico http legítimo).

3.5 - Si sólo va a probar este software, cualquier instalación LAMP o WAMP moderna 
es suficiente. Puede instalar fácilmente todo el software necesario desde
un paquete como XAMPP (http://sourceforge.net/projects/xampp/), que preinstala
Apache, Mysql, PHP, etc. de forma unificada y sin esfuerzo.
Pero una implementación de Gobierno Electrónico seria requiere un cortafuegos,
una auditoría de seguridad permanente con honeypots y detección de intrusiones, 
una política de respaldos diarios, de replicación de bases de datos, un entorno
chroot, un proxy saliente, etc.
La plataforma de gobierno electrónico 'Free-gov' sobre la que se basa este sistema
es totalmente segura en la medida que sea manejada por administradores de sistemas
competentes y concientes de que deben complementar toda instalación con las
diferentes herramientas de seguridad y respaldos disponibles para su sistema
operativo.
Como dice la documentación de 'Free-gov': "la seguridad de una implementación de
gobierno electrónico es directamente proporcional a la solidez profesional de
su administrador de sistemas"



4) INSTALACION

4.1 - Base de datos - Es necesario crear una serie de tablas en una base de datos 
MySQL. Estas tablas contienen la estructura ACL (permisos de acceso y usuarios),
así como las definiciones del módulo 'Voto Electrónico'.
Para automatizar la creación inicial de las tablas, se suministra un archivo de
nombre 'voto-electronico.sql' en la raíz del proyecto.
Use el archivo 'voto-electronico.sql' desde su herramienta de gestión de 
MySQL (phpMyAdmin por ejemplo), ejecute las instrucciones SQL del archivo y se
crearán automáticamente las estructuras de datos necesarias, además de ciertas
configuraciones iniciales preestablecidas, y datos de ejemplo, que usted puede 
borrar (usuarios, series de credencial, listas de votación).


4.2 - Configuración del archivo .configuration - Este es el archivo principal de 
configuraión del sistema, y se encuentra en la carpeta 'free-gov-core'. Si está 
en una plataforma UNIX (como Linux o FreeBSD) tenga presente que es un archivo 
oculto, y  configure su gestor de archivos y su cliente FTP para mostrar archivos
ocultos. Dentro de .configuration usted deberá configurar la URI del servidor 
MySQL (si el MySQL está en el mismo servidor web, ponga "loclhost", en caso 
contrario ponga el nombre o dirección IP del servidor de bases de datos). También
deberá poner el nombre de la base de datos a usar, el nombre de usuario y password 
de MySQL. Dentro de '.configuration' se puede configurar el texto que se verá en 
el título y en  el pie de cada página. Por último, la configuración de correo 
electrónico no es requerida en la instalación de 'Voto Electrónico'


4.3 - Personalización de imágenes y logos - En la carpeta 'http-root/images' hay 
una imagen de nombre 'topbanner-trans.png' que es la que aparece en la portada del
Panl de Administración. Puede ser sustituída por otra imagen PNG de las mismas
dimensiones y con el mismo nombre.
También hay un logotipo del municipio 'logomunicipio1.png'. Puede borrarlo y poner 
un logotipo personalizado, en el mismo entorno de dimensiones. 


4.4 - php.ini personalizado - La plataforma 'Free-gov' usa una configuración de 
PHP especial y optimizada (aunque no es un requerimiento forzoso). Si usted tiene
la posibilidad de manipular el php.ini global del servidor, use el archivo 
'php.ini' que se suministra dentro de la carpeta 'cgi-bin' del proyecto. 
Si no puede cambiar la configuración global de PHP, entonces siga las instrucciones 
del archivo README.txt suministrado en la carpeta 'cgi-bin'. Luego descomente las 
siguientes líneas, que son las primeras instrucciones del archivo .htaccess en la 
raíz de la instalación ("descomentar" o "quitar el comentario" es borrar el 
caracter # que precede la línea):

    #Options +ExecCGI
    #AddHandler php5-cgi .php
    #Action php-cgi /cgi-bin/php-wrapper.fcgi
    #Action php5-cgi /cgi-bin/php-wrapper.fcgi
    
La configuración del php.ini personalizado indicada en este paso no es forzosa, 
pero es clave para un uso más profesional de la plataforma de Gobierno Electrónico 
Free-gov (hay sistemas que en cada petición al front-controller establecen 
variables como zona horaria, nombre de las cookies por defecto, etc. El proyecto
Free-gov entiende que estos valores se deberían establecer sólo una vez durante
la instalación, aligerando el trabajo de CPU de cada petición, lo cual es muy
importante en servidores sujetos a mucha carga).



5) CREACION INICIAL DE USUARIOS Y PASSWORDS

Los usuarios (funcionarios que tendrán acceso al sistema con diferentes privilegios)
se crean en la base de datos, en la tabla 'acl_users'.
Existe un  usuario inicial, de nombre 'usuarioinicial' y cuyo password es 
'cambiarurgente'. Este usuario fue creado en la línea 117 del archivo 
'voto-electronico.sql':

INSERT INTO `acl_users` (`id`, `username`, `cryptpass`, `realname`) VALUES
(1, 'usuarioinicial', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Usuario');

Como se puede ver, en la base de datos no se guardan los passwords, sino una firma
hash (MD5 + SHA2) del mismo, que por razones de seguridad es irreversible.
Al crear un usuario nuevo, se hace desde el administrador de la base de datos (que
puede ser phpMyAdmin, por ejemplo). A cada usuario que se ingrese, se le puede 
poner en el campo de password la cadena 7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6 
entonces ese usuario tendrá como password la cadena 'cambiarurgente'. El usuario 
deberá ingresar a su cuenta inmediatamente y cambiar el password por uno de su
preferencia, el que a su vez se guardará encriptado. Si un usuario olvida su 
password, el administrador lo podrá resetear volviendo a poner la cadena 
7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6 para que el usuario acceda por única vez
con el password 'cambiarurgente'.

Luego de creados cada usuario, es necesario manipular una segunda tabla del ACL 
(Access Control List) para hacer que estos usuarios pertenezcan al grupo 
'elecciones_admin'. Esto se hace en la tabla 'acl_users2groups'. Cada usuario 
-una vez ingresado a la tabla 'acl_users'- tiene un número de ID autoincremental 
asociado. En la tabla 'acl_users2groups' simplemente hay dos campos ('user' y 
'group'), y la llenamos poniendo entradas con el ID de cada usuario, y la cadena 
de grupo 'elecciones_admin'.  Para ilustrar lo explicado, abajo se muestra la 
línea del archivo 'voto-electronico.sql' que establece los permisos del usuario 
'usuarioinicial' (cuyo id es '1'):

  INSERT INTO `acl_users2groups` (`user`, `group`) VALUES
  (1, 'elecciones_admin'),
  (1, 'elecciones_mesa');
  
En el ejemplo precedente, estamos haciendo que el usuario "1" pertenezca tanto
al grupo 'elecciones_admin' (administración del sistema) como al segundo grupo 
'elecciones_mesa' (miembros de mesa receptora de votos). Por tanto, este usuario
tendrá en su menú un acceso a todas las pantallas (votación, configutación, etc).

Si creamos un usuario pero olvidamos darle pertenencia por lo menos a un grupo,
cuando este usuario ingrese al sistema verá un mensaje de error indicando que
no pertenece a ningún grupo y que no tiene permisos para nada (Free-gov usa una
política de seguridad de restricción por defecto apta para Gobierno Electrónico).
  
  
  
6) INSTALACION COMO MODULO EN UNA PLATAFORMA FREE-GOV PREEXISTENTE 
 
Si su organismo ya dispone de una instalación de la plataforma de Gobierno 
Electrónico Free-gov, entonces considere integrar el Sistema 'Voto Electrónico'
como módulo de su instalación existente.
De esa forma, los usuarios de 'Voto Electrónico' verán aparecer los comandos
de este software en el menú de su pantalla habitual de Free-gov, y a la vez éste
seguirá inaccesible para los usuarios que no hayan sido explícitamente agregados
al grupo de administradores o al de receptores de 'Voto Electrónico'.

6.1 - Copia del módulo - en la carpeta 'modules' de su instalación existente de
Free-gov copie la carpeta 'elecciones' que se halla dentro de la carpeta 'modules'
de esta distribución.

6.2 - Archivo de aterrizaje - Para aquellos funcionarios que tengan acceso a otras 
funciones de su instalación Free-gov, el funcionamiento del sistema no presentará
cambios. Pero los funcionarios que sólo pertenezcan al grupo 'elecciones_admin'
necesitarán una pantalla "de aterrizaje" donde ingresar cuando entren al sistema.
El aterrizaje de 'Voto Electrónico' es el archivo 'elecciones_admin.inc' que 
se halla dentro de las carpetas 'modules/main' Debe copiarlo en la ruta 
'modules/main' de su instalación de Free-gov existente.

6.3 - Creación del grupo y los permisos ACL - Desde el gestor de MySQL (phpMyAdmin)
cree el grupo 'elecciones_admin' en la tabla de grupos 'acl_groups':

  INSERT INTO `acl_groups` (`name`, `description`) VALUES
  ('elecciones_admin', 'Gestiona sistema Voto Electronico'),
  ('elecciones_mesa',  'Funcionario receptor de votos');

Ahora debe crear el "mapa" que vincula al grupo con las diferentes operaciones 
permitidas, así como los elementos del menú que se crearán cuando corresponda.
Esto se realiza en la tabla 'acl_groups2res' que mapea los grupos a los recursos a
ser accesados, agregando las reglas para el grupo 'elecciones_admin'. Ejecute la 
siguiente instrucción SQL:

   INSERT INTO `acl_groups2res` (`id`, `group`, `module`, `operation`, `negative`, 
   `menu_group`, `menu_caption`) VALUES
   (12, 'elecciones_admin', 'elecciones', 'index', 0, NULL, NULL),
   (13, 'elecciones_admin', 'elecciones', 'serieshab', 0, 'Configuración acto 
         eleccionario', 'Series habilitadas'),
   (14, 'elecciones_admin', 'elecciones', 'serieshab_c', 0, NULL, NULL),
   (15, 'elecciones_admin', 'elecciones', 'serieshab_d', 0, NULL, NULL),
   (16, 'elecciones_admin', 'elecciones', 'listas', 0, 'Configuración acto 
         eleccionario', 'Gestionar Listas'),
   (17, 'elecciones_admin', 'elecciones', 'listas_c', 0, NULL, NULL),
   (18, 'elecciones_admin', 'elecciones', 'listas_d', 0, NULL, NULL),
   (19, 'elecciones_mesa', 'elecciones', 'votosmesa', 0, 'Acto eleccionario', 
        'Votos emitidos'),
   (20, 'elecciones_mesa', 'elecciones', 'votar', 0, 'Acto eleccionario', 
        'Emitir Voto'),
   (21, 'elecciones_mesa', 'elecciones', 'votar2', 0, NULL, NULL),
   (22, 'elecciones_admin', 'elecciones', 'circuitos', 0, 'Configuración acto 
         eleccionario', 'Gestionar Circuitos'),
   (23, 'elecciones_admin', 'elecciones', 'circuitos_c', 0, NULL, NULL),
   (24, 'elecciones_admin', 'elecciones', 'circuitos_d', 0, NULL, NULL),
   (25, 'elecciones_admin', 'elecciones', 'funcionarios', 0, 'Configuración 
         acto eleccionario', 'Gestionar funcionarios'),
   (26, 'elecciones_admin', 'elecciones', 'funcionarios_c', 0, NULL, NULL),
   (27, 'elecciones_admin', 'elecciones', 'funcionarios_d', 0, NULL, NULL),
   (28, 'elecciones_admin', 'elecciones', 'escrutinio', 0, 'Acto eleccionario', 
        'Escrutinio Global'),
   (29, 'elecciones_admin', 'elecciones', 'escrutiniocircuito', 0, 'Acto 
         eleccionario', 'Escrutinio Circuital'),
   (30, 'elecciones_mesa', 'elecciones', 'votosmesa_p', 0, NULL, NULL);
   

Por último agregue los usuarios que corresponda al grupo 'elecciones_admin', 
de esta forma no sólo tendrán acceso al módulo 'Voto Electrónico' sino que
además aparecerán los enlaces a las diferentes herramientas en el menú del
sistema del usuario. Un ejemplo de cómo agregar los usuarios con IDs 1, 5 y 100:

  INSERT INTO `acl_users2groups` (`user`, `group`) VALUES
  (1, 'elecciones_admin'),
  (1, 'elecciones_mesa'),
  (5, 'elecciones_admin'),
  (5, 'elecciones_mesa'),  
  (100, 'elecciones_admin');

  
6.4 - Concepto de módulo en el contexto de una plataforma e-gov modular - Free-gov 
fue concebido para permitir que en una misma instalación coexistan una cantidad 
de módulos diversos, permitiendo a cada usuario ver sólo aquellos que 
corresponden a su tarea, y simplificando la tarea de usuarios que requieren el
uso de varias herramientas al centralizarlas todas bajo un mismo proceso de login.
En la URI de un usuario logueado en panel de control podemos ver:
    https://www.sitio.gov/MODULO/OPERACION/PARAMETRO1/PARAMETRO2/PARAMETROn

En nuestro caso MODULO es 'elecciones', mientras OPERACION puede ser por ejemplo 
'circuitos_c', que es la pantalla desde donde se da de alta (create) un circuito.    



7) FUNDAMENTOS DE USO DEL SISTEMA

'Voto Electrónico' es un sistema con un subsistema de acceso privado (donde
los funcionarios configuran y mantienen los parámetros de un acto electoral) y
un subsistema semi-público (donde los funcionarios receptores de votos ingresan
los datos de los votantes, quienes luego eligen a solas, desde una pantalla
creada para el elector).
 
7.1 - Subsistema de administración de la elección  
Es un Panel de Control donde sólo acceden los funcionarios autorizados. Desde el 
Panel de Control se administra una base de  datos de elementos como Listas, 
Circuitos, Funcionarios receptores de votos, etc.
También es posible realizar escrutinios finales o parciales, globales o a nivel
de circuito.

    7.1.1 - Series habilitadas - Desde esta herramienta se mantiene la lista de
            Series de Credencial Cívica habilitadas para el acto eleccionario.
            En nuestra configuración, el acto eleccionario es de alcance municipal,
            por lo tanto s'olo se deja votar a vecinos del municipio (esta carac-
            terística puede ser reprogramada en caso de realizzarse una elección
            de otro alcance).
    7.1.2 - Gestionar listas - Desde esta herramienta, el administrador da de alta
            las listas que participarán en el acto eleccionario.
    7.1.3 - Gestionar circuitos - Desde esta herramienta, el administrador maneja
            los circuitos de recepción de votos. Es importante completar la carga 
            de circuitos antes de proceder a dar de alta los funcionarios receptores
            de votos, ya que el alta de los mismos requere la asociación a un 
            circuito específico.
    7.1.4 - Gestionar funcionarios - Desde esta herramienta se dan de alta los 
            funcionarios que trabajarán en las mesas receptoras de votos. Cada
            funcionario está vinculado a un circuito (o mesa receptora), y los votos
            gestionados por el funcionario se asignarán a su circuito vinculado. Por 
            eso es importante mantener esta información actualizada cuando un 
            funcionario es reasignado a otro circuito.

7.2 - Subsistema receptor de votos (mesa de votación)
Es el conjunto de pantallas desde donde los funcionarios receptores de votos
ingresan los datos de cada votante y validan que no haya votado aún. 
Si todo es correcto, se despliega la pantalla del votante. En ese momento, el
funcionario se retira y el votante queda oculto tras la mampara suministrada por 
la Corte Electoral. El ciudadano elige su opción de voto y la confirma.
Una vez se haya votado, se retorna a una pantalla donde aparece el listado de
personas que votaron en la mesa. Si el votante aparece en el listado (como primer
elemento de la lista), entonces queda confirmado que el voto se emitió de forma
exitosa. Desde ese listado se pueden imprimir los comprobantes de votación (desde
el ícono de impresora a la derecha del renglón de registro del votante).
El subsistema de acceso público procesa, valida y sanea su entrada a fin de evitar
ataques de tipo XSS o de inyección SQL.


7.3 - Asignación de votos a circuitos y auditoría de responsabilidades
En este software, cada funcionario receptor de votos tiene su propio acceso al 
sistema, con su nombre de usuario y contraseña. En una mesa receptora de votos,
el funcionario responsable de la PC en un determinado momento, debe estar al mando
de su propia sesión (en la pantalla aparece el nombre del funcionario responsable).
Cuando los funcionarios se alternen en el manejo de la PC, deben cerrar la sesión
y el nuevo funcionario debe iniciar sesión con sus datos. Se prohibe que un
funcionario esté trabajando en la sesión de otro funcionario. Adicionalmente, la
sesión se cierra automáticamente luego de 5 minutos de inactividad (al igual que
en la Banca Electrónica).
Cada funcionario es responsable por la actividad que se lleva a cabo en su sesión
de trabajo.
El sistema contabiliza los votos para cada funcionario, a la vez que lleva el
control de los inicios y cierres de sesión, así como de cualquier error que pudiera
surgir en las diferentes pantallas (números de documento mal ingresados, intentos
de ingreso de campos vacíos, etc).
El eje del control del sistema es la sesión del funcionario. Como a su vez cada
funcionario está asignado a un circuito, el software termina de componer los 
escrutinios por circuito sumando los votos ingresados por los funcionarios asignados.



8) REGISTROS DE ACTIVIDAD (LOGFILES)

Free-gov guarda los registros de actividad en la tabla 'log' de la base de datos.
Allí registra toda la actividad que se realiza en el sistema: ingreso de usuarios,
cierres de sesión, errores, intentos de ataques, etc. Para cada registro guarda
día y hora detallada, características de la máquina con la que se accede, datos
del uso de un posible servidor proxy (una técnica muy usada por atacantes), etc.
En el caso de ataques, el sistema encripta la cadena usada por el atacante y la
guarda en el registro, junto a la dirección IP del origen del ataque. Esto evita
ataques de tipo "inyección SQL".

Con toda esa información a almacenar, la tabla 'log' puede crecer desmedidamente,
por lo que se recomenda pasar periódicamente los datos a un soporte paralelo para
fines de archivo, y vaciar la tabla para mantener el servidor SQL más libre. 



9) LICENCIA DEL SOFTWARE

La licencia es AGPL versión 3 (Affero General Public License), creada por la Free 
Software Foundation y reconocida por OSI (Open Source Initiative).
Este software se distribuye bajo la misma licencia de Software Libre que utiliza 
la Plataforma de Gobierno Electrónico 'Free-gov' sobre la que fue desarrollado.
Este software se puede descargar, estudiar, modificar, instalar en cuantas PCs se
desee, se puede copiar, se puede dar a terceros con total libertad... la única
restricción que impone la licencia es que cuando Ud. copie el software y se lo
de a un tercero, lo haga acompañado del código fuente del programa, y con las
mismas libertades con que Ud. lo recibió (y bajo la misma licencia).
Una copia en inglés de la licencia acompaña al proyecto en el archivo 'license.txt'
La licencia original en inglés es la que tiene valor legal en todo el mundo, y se
aplica de acuerdo al Derecho Internacional y los tratados internacionales sobre 
Derechos de Autor.

Puede leer más acerca de esta licencia en:
    http://es.wikipedia.org/wiki/GNU_Affero_General_Public_License

Puede acceder al texto oficial completo de la licencia AGPL en:
    http://www.gnu.org/licenses/agpl.html

Al momento de escribir este documento lamentablemente no existían traducciones al
español del texto de la licencia AGPL.



10) POR QUE SE ELIGIO PHP COMO LENGUAJE PARA EL DESARROLLO DE ESTE SISTEMA

La elección de un lenguaje de programación es un tema pasional que suele provocar
"guerras santas" entre los partidarios de una u otra tecnología: es como la 
pertenencia a una religión, o como el ser hincha de un club deportivo.
Pero más allá de creencias ypasiones, la elección de un lenguaje tiene que 
fundarse en ventajas reales y demostrables, además de existir antecedentes del 
uso de esa tecnología en sistemas de misión crítica de gran porte.

Compartimos las mismas razones que el proyecto Free-gov enumera en su sitio:

- PHP es Software Libre, y además de ahorrar costos de licencias, su modelo de
desarrollo Open Source (con decenas de miles de programadores estudiando,
analizando y mejorando el producto) ha hecho de PHP la plataforma de desarrollo
para programación web más sólida y completa del mercado, superando con creces
a cualquier producto comercial.
- PHP actúa como un lenguaje interpretado, y sin embargo es posible compilar
los scripts para mejorar la velocidad de ejecución (ejemplo: Facebook)
- PHP es el más popular de los lenguajes de programación Server-Side, por lo
tanto es más sencillo hallar programadores calificados, colaboradores, etc. 
- PHP es multiplataforma y puede ser usado con cualquier sistema operativo, y
con cualquier servidor web. No estamos forzados a usar un sistema en particular
Existen instalaciones de PHP completamente usables funcionando 100% en la CPU
de teléfonos celulares; en el otro extremo, existen compilaciones de PHP 
corriendo en mainframes, supercomputadoras y clusters PVM. Si tiene un celular
con Android, instale "Web Server Ultimate" o "Bit Web Server" y ponga a funcionar
"Voto Electrónico" usando su celular como servidor.
- PHP es ampliamente usado en las empresas de hosting comercial, por tanto un
programa en PHP puede ser fácilmente migrado a cualquier servidor externo, aún
los de más bajo costo.
- PHP (cuando está debidamente instalado y configurado) es una plataforma de
extrema seguridad, perfectamente apta para Gobierno Electrónico, tal como lo
demuestra el proyecto Free-gov.
- PHP soporta programación de alto y bajo nivel (tan bajo como sockets TCP/IP)
- PHP está pre-empaquetado con Apache y MySQL por defecto en la mayoría de las 
distribuciones Linux, así como en FreeBSD, OpenBSD, Solaris, etc.
- PHP soporta tanto Programación Orientata a Obejtos (OOP) como Programación
Procedural Estructurada (esta última es la preferida por Free-gov).

PHP es la tecnología elegida por muchos de los sitios web más grandes del mundo:
Yahoo, Wikipedia, Facebook, Youtube, Flickr, Digg, y partes de Google.
PHP también es usado por aproximadamente el 82% de todos los servidores a nivel
mundial.

