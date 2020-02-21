# API

- api/v1/
  - /dustcarts/{dustcart_id}
  - /dustcarts/{dustcart_id}/handle
    - GET
    - POST
  - /dustcarts/{dustcart_id}/setting
    - GET
    - POST
  - /dustcarts/{dustcart_id}/logs/actions
    - GET
  - /dustcarts/{dustcart_id}/logs/images
    - GET

---

### DB 初期設定

```mysql
mysql> CREATE DATABASE MYSQL_DATABASE;
mysql> CREATE USER 'MYSQL_USER'@'MYSQL_HOST' IDENTIFIED BY 'MYSQL_PASSWORD';
mysql> GRANT ALL PRIVILEGES ON database_name.* TO 'MYSQL_USER'@'MYSQL_HOST';
mysql> FLUSH PRIVILEGES;

```

#### トラブルシューティング

- https://itips.krsw.biz/python-mysql-runtime-error-cryptography-required/
