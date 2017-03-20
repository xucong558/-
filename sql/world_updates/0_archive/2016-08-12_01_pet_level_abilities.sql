--
-- New table to hold hardcoded stuff
--
DROP TABLE IF EXISTS `pet_level_abilities`;
CREATE TABLE `pet_level_abilities` (
  `level` int(3) unsigned NOT NULL DEFAULT '0',
  `health` int(5) unsigned NOT NULL DEFAULT '0',
  `armor` int(5) unsigned NOT NULL DEFAULT '0',
  `strength` int(5) unsigned NOT NULL DEFAULT '0',
  `agility` int(5) unsigned NOT NULL DEFAULT '0',
  `stamina` int(5) unsigned NOT NULL DEFAULT '0',
  `intellect` int(5) unsigned NOT NULL DEFAULT '0',
  `spirit` int(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`level`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- hardcoded values from Pet.cpp
--
REPLACE INTO `pet_level_abilities` (`level`, `health`, `armor`, `strength`, `agility`, `stamina`, `intellect`, `spirit`) VALUES
	(1, 220, 15, 22, 15, 22, 20, 20),
	(2, 240, 16, 23, 16, 24, 20, 20),
	(3, 250, 41, 24, 16, 25, 20, 21),
	(4, 270, 76, 25, 16, 27, 20, 21),
	(5, 280, 120, 26, 17, 28, 20, 21),
	(6, 300, 174, 27, 18, 30, 21, 21),
	(7, 320, 239, 28, 18, 32, 21, 22),
	(8, 340, 316, 29, 19, 34, 21, 22),
	(9, 360, 406, 30, 20, 36, 21, 22),
	(10, 380, 512, 31, 20, 38, 21, 23),
	(11, 400, 538, 32, 20, 40, 21, 23),
	(12, 430, 573, 33, 21, 43, 21, 24),
	(13, 450, 608, 34, 23, 45, 21, 25),
	(14, 480, 642, 35, 23, 48, 22, 26),
	(15, 510, 677, 37, 24, 51, 22, 27),
	(16, 540, 713, 38, 25, 54, 22, 28),
	(17, 570, 748, 40, 26, 57, 22, 29),
	(18, 600, 782, 42, 27, 60, 22, 29),
	(19, 630, 817, 44, 28, 63, 22, 31),
	(20, 660, 852, 45, 30, 66, 22, 32),
	(21, 700, 888, 47, 30, 70, 23, 32),
	(22, 740, 922, 49, 30, 74, 23, 34),
	(23, 790, 957, 50, 32, 79, 23, 34),
	(24, 830, 992, 52, 33, 83, 23, 36),
	(25, 880, 1026, 53, 34, 88, 23, 37),
	(26, 930, 1061, 55, 35, 93, 23, 37),
	(27, 980, 1097, 56, 36, 98, 23, 39),
	(28, 1030, 1130, 58, 37, 103, 24, 39),
	(29, 1090, 1165, 60, 38, 109, 24, 41),
	(30, 1140, 1200, 61, 40, 114, 24, 42),
	(31, 1190, 1234, 63, 40, 119, 24, 42),
	(32, 1240, 1270, 64, 41, 124, 24, 44),
	(33, 1290, 1304, 66, 43, 129, 24, 44),
	(34, 1340, 1340, 67, 44, 134, 25, 46),
	(35, 1400, 1373, 69, 45, 140, 25, 47),
	(36, 1460, 1480, 70, 46, 146, 25, 48),
	(37, 1520, 1593, 72, 47, 152, 25, 49),
	(38, 1580, 1709, 74, 48, 158, 25, 49),
	(39, 1640, 1834, 76, 49, 164, 26, 51),
	(40, 1700, 1964, 78, 50, 170, 26, 52),
	(41, 1770, 2101, 81, 52, 177, 26, 53),
	(42, 1830, 2246, 86, 53, 183, 26, 54),
	(43, 1900, 2397, 91, 54, 190, 26, 55),
	(44, 1960, 2557, 97, 55, 196, 26, 56),
	(45, 2030, 2725, 102, 57, 203, 27, 58),
	(46, 2100, 2780, 104, 57, 210, 27, 58),
	(47, 2170, 2835, 106, 59, 217, 27, 60),
	(48, 2240, 2888, 108, 60, 224, 27, 60),
	(49, 2320, 2944, 110, 61, 232, 28, 62),
	(50, 2400, 2999, 113, 63, 240, 28, 63),
	(51, 2470, 3052, 115, 64, 247, 28, 64),
	(52, 2550, 3108, 117, 65, 255, 28, 65),
	(53, 2630, 3163, 119, 67, 263, 28, 66),
	(54, 2710, 3216, 122, 68, 271, 29, 68),
	(55, 2790, 3271, 124, 70, 279, 29, 69),
	(56, 2880, 3327, 127, 71, 288, 29, 70),
	(57, 2960, 3380, 129, 72, 296, 29, 71),
	(58, 3050, 3435, 131, 74, 305, 30, 72),
	(59, 3140, 3489, 134, 75, 314, 30, 73),
	(60, 3230, 3791, 136, 77, 323, 30, 75),
	(61, 3320, 4091, 139, 82, 332, 30, 78),
	(62, 3420, 4391, 141, 87, 342, 30, 80),
	(63, 3510, 4691, 144, 92, 351, 31, 84),
	(64, 3610, 4991, 146, 97, 361, 31, 86),
	(65, 3700, 5291, 149, 102, 370, 31, 88),
	(66, 3800, 5591, 151, 107, 380, 32, 91),
	(67, 3910, 5892, 154, 112, 391, 32, 93),
	(68, 4010, 6192, 156, 117, 401, 32, 95),
	(69, 4120, 6492, 159, 122, 412, 32, 96),
	(70, 4230, 6792, 162, 127, 423, 33, 99),
	(71, 4340, 7092, 165, 131, 434, 34, 102),
	(72, 4450, 7392, 168, 136, 445, 35, 105),
	(73, 4560, 7692, 171, 141, 456, 36, 108),
	(74, 4670, 7992, 174, 146, 467, 37, 111),
	(75, 4780, 8292, 177, 151, 478, 38, 114),
	(76, 4890, 8592, 181, 156, 489, 39, 117),
	(77, 5010, 8892, 184, 161, 501, 40, 120),
	(78, 5120, 9192, 187, 166, 512, 41, 123),
	(79, 5230, 9492, 190, 171, 523, 42, 126),
	(80, 5340, 9792, 193, 176, 534, 43, 129);

--
-- Update world_db_version
--
UPDATE `world_db_version` SET `LastUpdate` = '2016-08-12_01_pet_level_abilities' WHERE `LastUpdate` = '2016-07-17_01_misc';