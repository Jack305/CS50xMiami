-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Mar 25, 2017 at 03:13 PM
-- Server version: 5.5.50-0ubuntu0.14.04.1
-- PHP Version: 5.5.9-1ubuntu4.19

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `pset7`
--

-- --------------------------------------------------------

--
-- Table structure for table `history`
--

CREATE TABLE IF NOT EXISTS `history` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `action` char(5) NOT NULL,
  `symbol` char(10) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `shares` int(10) unsigned NOT NULL,
  `user_id` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=20 ;

--
-- Dumping data for table `history`
--

INSERT INTO `history` (`id`, `action`, `symbol`, `price`, `date`, `shares`, `user_id`) VALUES
(1, 'SELL', 'AAPL', 141.42, '2017-03-23 16:50:50', 0, 11),
(2, 'BUY', 'FREE', 1.15, '2017-03-23 16:54:56', 1000, 11),
(3, 'BUY', 'AAPL', 141.28, '2017-03-23 16:55:05', 125, 11),
(4, 'SELL', 'AAPL', 141.28, '2017-03-23 16:55:10', 125, 11),
(5, 'SELL', 'FREE', 1.15, '2017-03-23 16:55:15', 1000, 11),
(6, 'SELL', 'FREE', 1.15, '2017-03-23 16:58:39', 2500, 9),
(7, 'BUY', 'SNAP', 22.80, '2017-03-23 17:20:33', 100, 12),
(8, 'BUY', 'FREE', 1.15, '2017-03-23 17:20:46', 50, 12),
(9, 'BUY', 'FREE', 1.15, '2017-03-23 17:23:01', 0, 12),
(10, 'SELL', 'FREE', 1.15, '2017-03-23 17:23:14', 50, 12),
(11, 'BUY', 'FREE', 1.15, '2017-03-23 17:23:24', 0, 12),
(12, 'SELL', 'FREE', 1.15, '2017-03-23 17:24:28', 0, 12),
(13, 'SELL', 'SNAP', 22.80, '2017-03-23 17:24:34', 100, 12),
(14, 'BUY', 'FREE', 1.15, '2017-03-23 17:24:43', 0, 12),
(15, 'SELL', 'FREE', 1.15, '2017-03-23 17:25:49', 0, 12),
(16, 'BUY', 'FREE', 1.15, '2017-03-23 18:20:53', 100, 12),
(17, 'BUY', 'SNAP', 22.94, '2017-03-23 18:21:02', 200, 12),
(18, 'BUY', 'AAPL', 141.09, '2017-03-23 18:32:58', 1000, 12),
(19, 'SELL', 'AAPL', 141.23, '2017-03-23 18:46:14', 1000, 12);

-- --------------------------------------------------------

--
-- Table structure for table `portfolios`
--

CREATE TABLE IF NOT EXISTS `portfolios` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `symbol` char(255) NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `key_set` (`user_id`,`symbol`),
  KEY `id` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=38 ;

--
-- Dumping data for table `portfolios`
--

INSERT INTO `portfolios` (`id`, `user_id`, `symbol`, `shares`) VALUES
(36, 12, 'FREE', 100),
(37, 12, 'SNAP', 200);

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `hash` varchar(255) NOT NULL,
  `cash` decimal(12,2) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=13 ;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `username`, `hash`, `cash`) VALUES
(1, 'andi', '$2y$10$c.e4DK7pVyLT.stmHxgAleWq4yViMmkwKz3x8XCo4b/u3r8g5OTnS', 0.00),
(2, 'caesar', '$2y$10$0p2dlmu6HnhzEMf9UaUIfuaQP7tFVDMxgFcVs0irhGqhOxt6hJFaa', 0.00),
(3, 'eli', '$2y$10$COO6EnTVrCPCEddZyWeEJeH9qPCwPkCS0jJpusNiru.XpRN6Jf7HW', 0.00),
(4, 'hdan', '$2y$10$o9a4ZoHqVkVHSno6j.k34.wC.qzgeQTBHiwa3rpnLq7j2PlPJHo1G', 0.00),
(5, 'jason', '$2y$10$ci2zwcWLJmSSqyhCnHKUF.AjoysFMvlIb1w4zfmCS7/WaOrmBnLNe', 0.00),
(6, 'john', '$2y$10$dy.LVhWgoxIQHAgfCStWietGdJCPjnNrxKNRs5twGcMrQvAPPIxSy', 0.00),
(7, 'levatich', '$2y$10$fBfk7L/QFiplffZdo6etM.096pt4Oyz2imLSp5s8HUAykdLXaz6MK', 0.00),
(8, 'rob', '$2y$10$3pRWcBbGdAdzdDiVVybKSeFq6C50g80zyPRAxcsh2t5UnwAkG.I.2', 0.00),
(9, 'skroob', '$2y$10$395b7wODm.o2N7W5UZSXXuXwrC0OtFB17w4VjPnCIn/nvv9e4XUQK', 2875.00),
(10, 'zamyla', '$2y$10$UOaRF0LGOaeHG4oaEkfO4O7vfI34B1W23WqHr9zCpXL68hfQsS3/e', 0.00),
(11, 'enagimov', '$2y$10$YaS8Yf7SpfxHChNsPAE99u2PeOMgDn8EaK3z8fQ6w1lGTwpjSd58u', 154953.12),
(12, 'jack', '$2y$10$B7HpzM3e7tuA96B5DKKsX.D1HnI4tiUJ7GZzqakKVYqbE8Cb7xwzC', 1035433.89);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
