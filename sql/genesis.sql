--
-- Table structure for table `crawl_pool`
--

DROP TABLE IF EXISTS `crawl_pool`;

CREATE TABLE `crawl_pool` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `url` varchar(300) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_url` (`url`)
) ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=utf8;
