
CREATE USER 'inventaari'@'%' IDENTIFIED BY PASSWORD '*0EE04DF57962256876CDC0A4494A526634E023E9';

CREATE DATABASE inventaari
	DEFAULT CHARACTER SET utf8
	DEFAULT COLLATE utf8_general_ci;

USE inventaari;

CREATE TABLE products
(  code CHAR(12) NOT NULL 
,	name VARCHAR(200) NOT NULL
,	price NUMERIC(22,2) NOT NULL
,	stock INTEGER NOT NULL
,	CONSTRAINT products_pkey PRIMARY KEY (code)
,	CONSTRAINT products_name UNIQUE products_name_key (name)
);
Create table sales_event(
	sales_event_id  integer(10) NOT NULL AUTO_INCREMENT,
	seller_id char(12) ,
	total_sum decimal(22,2),
	sale_time datetime,
	PRIMARY KEY (sales_event_id)
);

create table sales_row(
	row_id MEDIUMINT NOT NULL AUTO_INCREMENT,
	event_id integer(10),
	product_code char(12),
	amount decimal(22,2),
	PRIMARY KEY (row_id),

 FOREIGN KEY (event_id) REFERENCES sales_event (sales_event_id)
 ON DELETE CASCADE ON UPDATE cascade,

 FOREIGN KEY (product_code) REFERENCES products (code)
 ON DELETE CASCADE ON UPDATE cascade
);

CREATE TABLE users
(
	name VARCHAR(200) NOT NULL
	, card_id CHAR(10) NOT NULL
	, user_password VARCHAR(50) NOT NULL

);

GRANT SELECT, INSERT, UPDATE, DELETE ON users TO 'inventaari'@'%';
GRANT SELECT, INSERT, UPDATE, DELETE ON sales_event TO 'inventaari'@'%';
GRANT SELECT, INSERT, UPDATE, DELETE ON sales_row TO 'inventaari'@'%';
GRANT SELECT, INSERT, UPDATE, DELETE ON products TO 'inventaari'@'%';

