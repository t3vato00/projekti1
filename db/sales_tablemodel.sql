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

GRANT SELECT, INSERT, UPDATE, DELETE ON sales_event TO 'inventaari'@'%';
GRANT SELECT, INSERT, UPDATE, DELETE ON sales_row TO 'inventaari'@'%';