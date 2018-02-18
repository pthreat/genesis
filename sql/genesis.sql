DROP TABLE IF EXISTS `crawl_pool`;

CREATE TABLE `crawl_pool` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `server` varchar(20) NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `inspected` tinyint(4) NOT NULL DEFAULT '0',
  `scheme` varchar(8) NOT NULL DEFAULT 'http',
  `url` varchar(300) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_scheme_url` (`scheme`,`url`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `rslvr`;

CREATE TABLE `rslvr` (
	`crawl_pool` int(10) unsigned NOT NULL,
	`addr` varchar(45) NOT NULL,
	UNIQUE KEY `idx_crawl_pool_addr` (`crawl_pool`,`addr`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
