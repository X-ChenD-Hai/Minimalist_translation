PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "language"(
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,
    zh_name char(20)  NOT NULL UNIQUE,
    en_name char(20)  NOT NULL UNIQUE,
    code char(10) NOT NULL UNIQUE 
);
INSERT INTO language VALUES(1,'阿拉伯语','Arabic','ar');
INSERT INTO language VALUES(2,'德语','German','de');
INSERT INTO language VALUES(3,'英语','English','en');
INSERT INTO language VALUES(4,'西班牙语','Spanish','es');
INSERT INTO language VALUES(5,'法语','French','fr');
INSERT INTO language VALUES(6,'印地语','Hindi','hi');
INSERT INTO language VALUES(7,'印度尼西亚语','Indonesian','id');
INSERT INTO language VALUES(8,'意大利语','Italian','it');
INSERT INTO language VALUES(9,'日语','Japanese','ja');
INSERT INTO language VALUES(10,'韩语','Korean','ko');
INSERT INTO language VALUES(11,'荷兰语','Dutch','nl');
INSERT INTO language VALUES(12,'葡萄牙语','Portuguese','pt');
INSERT INTO language VALUES(13,'俄语','Russian','ru');
INSERT INTO language VALUES(14,'泰语','hai','th');
INSERT INTO language VALUES(15,'越南语','Vietnamese','vi');
INSERT INTO language VALUES(16,'简体中文','Chinese-CHS','zh-CHS');
INSERT INTO language VALUES(17,'繁体中文','Chinese-CHT','zh-CHT');
INSERT INTO language VALUES(18,'南非荷兰语','Afrikaans','af');
INSERT INTO language VALUES(19,'阿姆哈拉语','Amharic','am');
INSERT INTO language VALUES(20,'阿塞拜疆语','Azeerbaijani','az');
INSERT INTO language VALUES(21,'白俄罗斯语','Belarusian','be');
INSERT INTO language VALUES(22,'保加利亚语','Bulgarian','bg');
INSERT INTO language VALUES(23,'孟加拉语','Bangla','bn');
INSERT INTO language VALUES(24,'波斯尼亚语','Bosnian (Latin)','bs');
INSERT INTO language VALUES(25,'加泰隆语','Catalan','ca');
INSERT INTO language VALUES(26,'宿务语','Cebuano','ceb');
INSERT INTO language VALUES(27,'科西嘉语','Corsican','co');
INSERT INTO language VALUES(28,'捷克语','Czech','cs');
INSERT INTO language VALUES(29,'威尔士语','Welsh','cy');
INSERT INTO language VALUES(30,'丹麦语','Danish','da');
INSERT INTO language VALUES(31,'希腊语','Greek','el');
INSERT INTO language VALUES(32,'世界语','Esperanto','eo');
INSERT INTO language VALUES(33,'爱沙尼亚语','Estonian','et');
INSERT INTO language VALUES(34,'巴斯克语','Basque','eu');
INSERT INTO language VALUES(35,'波斯语','Persian','fa');
INSERT INTO language VALUES(36,'芬兰语','Finnish','fi');
INSERT INTO language VALUES(37,'斐济语','Fijian','fj');
INSERT INTO language VALUES(38,'弗里西语','Frisian','fy');
INSERT INTO language VALUES(39,'爱尔兰语','Irish','ga');
INSERT INTO language VALUES(40,'苏格兰盖尔语','Scots','gd');
INSERT INTO language VALUES(41,'加利西亚语','Galician','gl');
INSERT INTO language VALUES(42,'古吉拉特语','Gujarati','gu');
INSERT INTO language VALUES(43,'豪萨语','Hausa','ha');
INSERT INTO language VALUES(44,'夏威夷语','Hawaiian','haw');
INSERT INTO language VALUES(45,'希伯来语','Hebrew','he');
INSERT INTO language VALUES(46,'克罗地亚语','Croatian','hr');
INSERT INTO language VALUES(47,'海地克里奥尔语','Haitian','ht');
INSERT INTO language VALUES(48,'匈牙利语','Hungarian','hu');
INSERT INTO language VALUES(49,'亚美尼亚语','Armenian','hy');
INSERT INTO language VALUES(50,'伊博语','Igbo','ig');
INSERT INTO language VALUES(51,'冰岛语','Icelandic','is');
INSERT INTO language VALUES(52,'爪哇语','Javanese','jw');
INSERT INTO language VALUES(53,'格鲁吉亚语','Georgian','ka');
INSERT INTO language VALUES(54,'哈萨克语','Kazakh','kk');
INSERT INTO language VALUES(55,'高棉语','Khmer','km');
INSERT INTO language VALUES(56,'卡纳达语','Kannada','kn');
INSERT INTO language VALUES(57,'库尔德语','Kurdish','ku');
INSERT INTO language VALUES(58,'柯尔克孜语','Kyrgyz','ky');
INSERT INTO language VALUES(59,'拉丁语','Latin','la');
INSERT INTO language VALUES(60,'卢森堡语','Luxembourgish','lb');
INSERT INTO language VALUES(61,'老挝语','Lao','lo');
INSERT INTO language VALUES(62,'立陶宛语','Lithuanian','lt');
INSERT INTO language VALUES(63,'拉脱维亚语','Latvian','lv');
INSERT INTO language VALUES(64,'马尔加什语','Malagasy','mg');
INSERT INTO language VALUES(65,'毛利语','Maori','mi');
INSERT INTO language VALUES(66,'马其顿语','Macedonian','mk');
INSERT INTO language VALUES(67,'马拉雅拉姆语','Malayalam','ml');
INSERT INTO language VALUES(68,'蒙古语','Mongolian','mn');
INSERT INTO language VALUES(69,'马拉地语','Marathi','mr');
INSERT INTO language VALUES(70,'马来语','Malay','ms');
INSERT INTO language VALUES(71,'马耳他语','Maltese','mt');
INSERT INTO language VALUES(72,'白苗语','Hmong','mww');
INSERT INTO language VALUES(73,'缅甸语','Myanmar (Burmese)','my');
INSERT INTO language VALUES(74,'尼泊尔语','Nepali','ne');
INSERT INTO language VALUES(75,'挪威语','Norwegian','no');
INSERT INTO language VALUES(76,'齐切瓦语','Nyanja (Chichewa)','ny');
INSERT INTO language VALUES(77,'克雷塔罗奥托米语','Querétaro Otomi','otq');
INSERT INTO language VALUES(78,'旁遮普语','Punjabi','pa');
INSERT INTO language VALUES(79,'波兰语','Polish','pl');
INSERT INTO language VALUES(80,'普什图语','Pashto','ps');
INSERT INTO language VALUES(81,'罗马尼亚语','Romanian','ro');
INSERT INTO language VALUES(82,'信德语','Sindhi','sd');
INSERT INTO language VALUES(83,'僧伽罗语','Sinhala (Sinhalese)','si');
INSERT INTO language VALUES(84,'斯洛伐克语','Slovak','sk');
INSERT INTO language VALUES(85,'斯洛文尼亚语','Slovenian','sl');
INSERT INTO language VALUES(86,'萨摩亚语','Samoan','sm');
INSERT INTO language VALUES(87,'修纳语','Shona','sn');
INSERT INTO language VALUES(88,'索马里语','Somali','so');
INSERT INTO language VALUES(89,'阿尔巴尼亚语','Albanian','sq');
INSERT INTO language VALUES(90,'塞尔维亚语(西里尔文)','Serbian (Cyrillic)','sr-Cyrl');
INSERT INTO language VALUES(91,'塞尔维亚语(拉丁文)','Serbian (Latin)','sr-Latn');
INSERT INTO language VALUES(92,'塞索托语','Sesotho','st');
INSERT INTO language VALUES(93,'巽他语','Sundanese','su');
INSERT INTO language VALUES(94,'瑞典语','Swedish','sv');
INSERT INTO language VALUES(95,'斯瓦希里语','Kiswahili','sw');
INSERT INTO language VALUES(96,'泰米尔语','Tamil','ta');
INSERT INTO language VALUES(97,'泰卢固语','Telugu','te');
INSERT INTO language VALUES(98,'塔吉克语','Tajik','tg');
INSERT INTO language VALUES(99,'菲律宾语','Filipino','tl');
INSERT INTO language VALUES(100,'克林贡语','Klingon','tlh');
INSERT INTO language VALUES(101,'汤加语','Tongan','to');
INSERT INTO language VALUES(102,'土耳其语','Turkish','tr');
INSERT INTO language VALUES(103,'塔希提语','Tahitian','ty');
INSERT INTO language VALUES(104,'乌克兰语','Ukrainian','uk');
INSERT INTO language VALUES(105,'乌尔都语','Urdu','ur');
INSERT INTO language VALUES(106,'乌兹别克语','Uzbek','uz');
INSERT INTO language VALUES(107,'南非科萨语','Xhosa','xh');
INSERT INTO language VALUES(108,'意第绪语','Yiddish','yi');
INSERT INTO language VALUES(109,'约鲁巴语','Yoruba','yo');
INSERT INTO language VALUES(110,'尤卡坦玛雅语','Yucatec','yua');
INSERT INTO language VALUES(111,'粤语','Cantonese (Traditional)','yue');
INSERT INTO language VALUES(112,'南非祖鲁语','Zulu','zu');
INSERT INTO language VALUES(113,'自动检测','Automatic detection','auto');
DELETE FROM sqlite_sequence;
INSERT INTO sqlite_sequence VALUES('language',113);
COMMIT;
