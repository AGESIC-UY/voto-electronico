-- phpMyAdmin SQL Dump
-- version 4.5.3.1
-- http://www.phpmyadmin.net
--
-- Generation Time: Apr 05, 2016 at 11:04 AM
-- Server version: 5.6.25-log
-- PHP Version: 7.0.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

-- --------------------------------------------------------

--
-- Table structure for table `acl_groups`
--

CREATE TABLE `acl_groups` (
  `name` varchar(20) NOT NULL,
  `description` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `acl_groups`
--

INSERT INTO `acl_groups` (`name`, `description`) VALUES
('elecciones_admin', 'Administra Elecciones'),
('elecciones_mesa', 'Receptor de votos');

-- --------------------------------------------------------

--
-- Table structure for table `acl_groups2res`
--

CREATE TABLE `acl_groups2res` (
  `id` int(11) NOT NULL,
  `group` varchar(20) NOT NULL,
  `module` varchar(60) NOT NULL COMMENT 'resource is: module/operation',
  `operation` varchar(30) NOT NULL COMMENT 'resource is: module/operation',
  `negative` tinyint(1) NOT NULL DEFAULT '0',
  `menu_group` varchar(65) DEFAULT NULL,
  `menu_caption` varchar(65) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `acl_groups2res`
--

INSERT INTO `acl_groups2res` (`id`, `group`, `module`, `operation`, `negative`, `menu_group`, `menu_caption`) VALUES
(12, 'elecciones_admin', 'elecciones', 'index', 0, NULL, NULL),
(13, 'elecciones_admin', 'elecciones', 'serieshab', 0, 'Configuración acto eleccionario', 'Series habilitadas'),
(14, 'elecciones_admin', 'elecciones', 'serieshab_c', 0, NULL, NULL),
(15, 'elecciones_admin', 'elecciones', 'serieshab_d', 0, NULL, NULL),
(16, 'elecciones_admin', 'elecciones', 'listas', 0, 'Configuración acto eleccionario', 'Gestionar Listas'),
(17, 'elecciones_admin', 'elecciones', 'listas_c', 0, NULL, NULL),
(18, 'elecciones_admin', 'elecciones', 'listas_d', 0, NULL, NULL),
(19, 'elecciones_mesa', 'elecciones', 'votosmesa', 0, 'Acto eleccionario', 'Votos emitidos'),
(20, 'elecciones_mesa', 'elecciones', 'votar', 0, 'Acto eleccionario', 'Emitir Voto'),
(21, 'elecciones_mesa', 'elecciones', 'votar2', 0, NULL, NULL),
(22, 'elecciones_admin', 'elecciones', 'circuitos', 0, 'Configuración acto eleccionario', 'Gestionar Circuitos'),
(23, 'elecciones_admin', 'elecciones', 'circuitos_c', 0, NULL, NULL),
(24, 'elecciones_admin', 'elecciones', 'circuitos_d', 0, NULL, NULL),
(25, 'elecciones_admin', 'elecciones', 'funcionarios', 0, 'Configuración acto eleccionario', 'Gestionar funcionarios'),
(26, 'elecciones_admin', 'elecciones', 'funcionarios_c', 0, NULL, NULL),
(27, 'elecciones_admin', 'elecciones', 'funcionarios_d', 0, NULL, NULL),
(28, 'elecciones_admin', 'elecciones', 'escrutinio', 0, 'Acto eleccionario', 'Escrutinio Global'),
(29, 'elecciones_admin', 'elecciones', 'escrutiniocircuito', 0, 'Acto eleccionario', 'Escrutinio Circuital'),
(30, 'elecciones_mesa', 'elecciones', 'votosmesa_p', 0, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `acl_metagroups`
--

CREATE TABLE `acl_metagroups` (
  `name` varchar(20) NOT NULL,
  `description` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `acl_metagroups2groups`
--

CREATE TABLE `acl_metagroups2groups` (
  `id` int(11) NOT NULL,
  `metagroup` varchar(20) NOT NULL,
  `group` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `acl_users`
--

CREATE TABLE `acl_users` (
  `id` int(11) NOT NULL,
  `username` varchar(20) NOT NULL,
  `cryptpass` varchar(40) NOT NULL,
  `realname` varchar(40) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `acl_users`
--

INSERT INTO `acl_users` (`id`, `username`, `cryptpass`, `realname`) VALUES
(1, 'usuarioinicial', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Usuario de prueba'),
(2, 'irismontesdeoca', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Iris Montes de Oca'),
(3, 'dianagamboa', '903b5d13d51a8b430351935465d348df40ed02ce', 'Diana Gamboa'),
(4, 'gracielagarcia', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Graciela García'),
(5, 'gracielabritos', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Graciela Britos'),
(6, 'cnavarro', '7e2e574b33c4ed677e528d1ab75b7dc8a2e0feeb', 'Cristina Navarro'),
(7, 'soniasuarez', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Sonia Suárez'),
(8, 'jsellanes', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Jacqueline Sellanes'),
(9, 'ilianaperez', '59d37f58b2625d23f309adc270af14dd77c1d7f5', 'Iliana Pérez'),
(10, 'fannyobando', '29bfe224d45e7b9ea3b74ac7f2e41b2ab1832e11', 'Fanny Obando'),
(11, 'estelagasco', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Estela Gasco'),
(12, 'ealmeida', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Emilia Almeida'),
(13, 'alejandraaquino', 'a43fd27e573797a0fecae5a37248e85cc093d2c3', 'Alejandra Aquino'),
(14, 'mgastambide', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Martha Gastambide'),
(15, 'javierdeleon', '469958950449fa2abd2eb8df41e984b242ce9091', 'Javier de León'),
(16, 'lfajardo', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Leticia Fajardo'),
(17, 'mcomesana', 'bca6937ff91ddf78d7d1f5c1fe77047b04604002', 'Martha Comesañas'),
(18, 'nsanchez', '88eac02a7d5361ae4420cb57cbba7c0661f84fe6', 'Nelly Sánchez'),
(19, 'palvarez', '9fa484676557ea1b2650f9d730fe5775a5513b1a', 'Perla Alvarez'),
(20, 'rcastellanos', 'd2114454af72444f6adc696f65b1ea7698a54940', 'Rosa Castellanos'),
(21, 'fmastrangelo', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Francisco Mastrangelo'),
(22, 'dsilveira', '270ba24e61cdf9d5b2c1478096f80c827a4623fe', 'Darío Silveira'),
(23, 'fernandadiaz', 'a7b901b582adddbec1626fe287111b2d7ef3fbed', 'Fernanda Díaz'),
(24, 'mariajose', '46cdb442e4686676edf0ee84dbcb8b72ac349e9d', 'María José Peña'),
(25, 'erodriguez', '3375a5311a90b08fa3d8d823abc8c643a5e73a85', 'Estela Rodríguez'),
(26, 'dbareno', '14f594a2db6da3db12297d44ad2c3c51d992eda6', 'Dardo Bareño');

-- --------------------------------------------------------

--
-- Table structure for table `acl_users2groups`
--

CREATE TABLE `acl_users2groups` (
  `user` int(11) NOT NULL,
  `group` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `acl_users2groups`
--

INSERT INTO `acl_users2groups` (`user`, `group`) VALUES
(1, 'elecciones_admin'),
(1, 'elecciones_mesa'),
(2, 'elecciones_mesa'),
(3, 'elecciones_mesa'),
(4, 'elecciones_mesa'),
(5, 'elecciones_mesa'),
(6, 'elecciones_mesa'),
(7, 'elecciones_mesa'),
(8, 'elecciones_mesa'),
(9, 'elecciones_mesa'),
(10, 'elecciones_mesa'),
(11, 'elecciones_mesa'),
(12, 'elecciones_mesa'),
(13, 'elecciones_mesa'),
(14, 'elecciones_mesa'),
(15, 'elecciones_mesa'),
(16, 'elecciones_mesa'),
(17, 'elecciones_mesa'),
(18, 'elecciones_mesa'),
(19, 'elecciones_mesa'),
(20, 'elecciones_mesa'),
(21, 'elecciones_mesa'),
(22, 'elecciones_mesa'),
(23, 'elecciones_mesa'),
(24, 'elecciones_mesa'),
(25, 'elecciones_mesa'),
(26, 'elecciones_mesa');

-- --------------------------------------------------------

--
-- Table structure for table `acl_users2metagroups`
--

CREATE TABLE `acl_users2metagroups` (
  `user` int(11) NOT NULL,
  `metagroup` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `elecciones_circuitos`
--

CREATE TABLE `elecciones_circuitos` (
  `id` int(11) NOT NULL,
  `name` varchar(120) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `elecciones_circuitos`
--

INSERT INTO `elecciones_circuitos` (`id`, `name`) VALUES
(1, 'Circuito 1 - Municipio de Maldonado'),
(2, 'Circuito 2 - Comunal Barrio Odizzio'),
(3, 'Circuito 3 - Comunal Maldonado Nuevo'),
(4, 'Circuito 4 - Comunal Santa Teresita'),
(5, 'Circuito 5 - Comunal Biarritz-La Candelaria'),
(6, 'Circuito 6 - Comunal Barrio Hipódromo'),
(7, 'Circuito 7 - Comunal El Molino'),
(8, 'Circuito 8 - Comunal San Francisco'),
(9, 'Circuito 9 - Comunal Villa Delia'),
(10, 'Circuito 10 - Comunal La Loma'),
(11, 'Circuito 11 - Salón Multiuso Cerro Pelado');

-- --------------------------------------------------------

--
-- Table structure for table `elecciones_funcionarios`
--

CREATE TABLE `elecciones_funcionarios` (
  `id` int(11) NOT NULL,
  `name` varchar(60) NOT NULL,
  `userid` int(11) NOT NULL,
  `username` varchar(30) NOT NULL,
  `circuito` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `elecciones_funcionarios`
--

INSERT INTO `elecciones_funcionarios` (`id`, `name`, `userid`, `username`, `circuito`) VALUES
(1, 'Jacqueline Sellanes', 8, 'jsellanes', 1),
(3, 'Alejandra Aquino', 13, 'alejandraaquino', 1),
(4, 'Leticia Fajardo', 16, 'lfajardo', 2),
(5, 'Martha Comesaña', 17, 'mcomesanas', 2),
(6, 'Javier De León', 15, 'javierdeleon', 3),
(7, 'Nelly Sánchez', 18, 'nsanchez', 3),
(8, 'Graciela García', 4, 'gracielagarcia', 4),
(9, 'Fernanda Díaz', 23, 'fernandadiaz', 4),
(10, 'Cristina Navarro', 6, 'cnavarro', 5),
(11, 'Emilia Almeida', 12, 'ealmeida', 5),
(12, 'María José Peña', 24, 'mariajose', 6),
(13, 'Iliana Pérez', 9, 'ilianaperez', 6),
(14, 'Graciela Britos', 5, 'gracielabritos', 7),
(15, 'Rosa Castellanos', 20, 'rcastellanos', 7),
(16, 'Sonia Suarez', 7, 'soniasuarez', 8),
(17, 'Estela Gasco', 11, 'estelagasco', 8),
(18, 'Fanny Obando', 10, 'fannyobando', 9),
(19, 'Perla Alvarez', 19, 'palvarez', 9),
(20, 'Estela Rodríguez', 25, 'erodriguez', 10),
(21, 'Dardo Bareño', 26, 'dbareno', 10),
(22, 'Diana Gamboa', 3, 'dianagamboa', 11),
(23, 'Martha Gastambide', 14, 'mgastambide', 11);

-- --------------------------------------------------------

--
-- Table structure for table `elecciones_listas`
--

CREATE TABLE `elecciones_listas` (
  `id` int(11) NOT NULL,
  `name` varchar(120) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `elecciones_listas`
--

INSERT INTO `elecciones_listas` (`id`, `name`) VALUES
(1, 'Lista 1 - Crecer con Futuro'),
(2, 'Lista 3 - Asociación Civil Juana Guerra'),
(3, 'Lista 4 - Centro de Rehabilitación Ecuestre'),
(4, 'Lista 5 - Asociación Down'),
(5, 'Lista 6 - Amor Exigente en Acción'),
(6, 'Lista 7 - Cerema'),
(7, 'Lista 8 - Atletas especiales Región Este'),
(8, 'Lista 9 - ONG CECORE'),
(9, 'Lista 10 -  Merendero Despertar Mdo. Nuevo'),
(10, 'Lista 11 - Centro Cultural Teatro de la Mancha'),
(11, 'Lista 14 - ADIMO'),
(12, 'Lista 15 - ADIM'),
(13, 'Lista 17 - Hogar Ginés Cairo Medina'),
(14, 'Lista 18 - Hogares Beraca'),
(15, 'Lista 19 - Centro Cultural Lengue Lengue'),
(16, 'Lista 20 - UNI3'),
(17, 'Lista 23 - Club de Leones'),
(18, 'Lista 24 - Comisión Barrio Lausana'),
(19, 'Lista 25 -  Com. Fomento Lomas Santa Teresita'),
(20, 'Lista 27 -  Espacio Vecinal San Antonio'),
(21, 'Lista 28 - Radio Comunitaria Digital en la web'),
(22, 'Lista 29 - Com. Fomento  Biarritz-La Candelaria'),
(23, 'Lista 30 - Aeroclub Punta del Este'),
(24, 'Lista 31 - Socobioma');

-- --------------------------------------------------------

--
-- Table structure for table `elecciones_serieshab`
--

CREATE TABLE `elecciones_serieshab` (
  `id` int(11) NOT NULL,
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `elecciones_serieshab`
--

INSERT INTO `elecciones_serieshab` (`id`, `name`) VALUES
(1, 'DAA'),
(2, 'DAC'),
(3, 'DAD'),
(4, 'DAE'),
(5, 'DAF'),
(6, 'DAG'),
(7, 'DAH'),
(8, 'DAI'),
(9, 'DAJ');

-- --------------------------------------------------------

--
-- Table structure for table `elecciones_votos`
--

CREATE TABLE `elecciones_votos` (
  `id` int(11) NOT NULL,
  `name` varchar(120) NOT NULL,
  `apellidos` varchar(60) NOT NULL,
  `nombres` varchar(60) NOT NULL,
  `numerocedula` varchar(12) DEFAULT NULL,
  `seriecredencial` int(11) DEFAULT NULL,
  `numerocredencial` varchar(6) DEFAULT NULL,
  `hora` time NOT NULL,
  `usuariosesion` int(11) NOT NULL,
  `voto` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- --------------------------------------------------------

--
-- Table structure for table `log`
--

CREATE TABLE `log` (
  `datetime` datetime NOT NULL,
  `ip` varchar(46) NOT NULL,
  `xforwardedf` varchar(46) DEFAULT NULL,
  `useragent` text NOT NULL,
  `userid` int(11) NOT NULL,
  `event` varchar(15) NOT NULL,
  `details` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `acl_groups`
--
ALTER TABLE `acl_groups`
  ADD UNIQUE KEY `name` (`name`);

--
-- Indexes for table `acl_groups2res`
--
ALTER TABLE `acl_groups2res`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `acl_metagroups`
--
ALTER TABLE `acl_metagroups`
  ADD UNIQUE KEY `name` (`name`);

--
-- Indexes for table `acl_metagroups2groups`
--
ALTER TABLE `acl_metagroups2groups`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `acl_users`
--
ALTER TABLE `acl_users`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `acl_users2groups`
--
ALTER TABLE `acl_users2groups`
  ADD KEY `user` (`user`);

--
-- Indexes for table `acl_users2metagroups`
--
ALTER TABLE `acl_users2metagroups`
  ADD KEY `user` (`user`);

--
-- Indexes for table `elecciones_circuitos`
--
ALTER TABLE `elecciones_circuitos`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `elecciones_funcionarios`
--
ALTER TABLE `elecciones_funcionarios`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `elecciones_listas`
--
ALTER TABLE `elecciones_listas`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `elecciones_serieshab`
--
ALTER TABLE `elecciones_serieshab`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `elecciones_votos`
--
ALTER TABLE `elecciones_votos`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `log`
--
ALTER TABLE `log`
  ADD PRIMARY KEY (`datetime`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `acl_groups2res`
--
ALTER TABLE `acl_groups2res`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=31;
--
-- AUTO_INCREMENT for table `acl_metagroups2groups`
--
ALTER TABLE `acl_metagroups2groups`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `acl_users`
--
ALTER TABLE `acl_users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;
--
-- AUTO_INCREMENT for table `elecciones_circuitos`
--
ALTER TABLE `elecciones_circuitos`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
--
-- AUTO_INCREMENT for table `elecciones_funcionarios`
--
ALTER TABLE `elecciones_funcionarios`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=24;
--
-- AUTO_INCREMENT for table `elecciones_listas`
--
ALTER TABLE `elecciones_listas`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=25;
--
-- AUTO_INCREMENT for table `elecciones_serieshab`
--
ALTER TABLE `elecciones_serieshab`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

-- --------------------------------------------------------

--
-- End of file
--
