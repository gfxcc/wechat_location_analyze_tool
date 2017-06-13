#ifndef _WECHAT_ANALYZE_SQL_H_
#define _WECHAT_ANALYZE_SQL_H_

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <error.h>
#include <memory>
#include <fstream>

/*
 *   Include directly the different
 *     headers from cppconn/ and mysql_driver.h + mysql_util.h
 *       (and mysql_connection.h). This will reduce your build time!
 *       */

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class Sql {
public:
  static Sql& GetInstance() {
    static Sql sql_helper;
    return sql_helper;
  }
  Sql() : output_("./output/db_dump.sql") {
    driver_ = get_driver_instance();
    if ((con_ = driver_->connect("34.224.71.115:3306", "yong", "123")) == NULL) {
      std::cout << "Error: failed to connect to database" << std::endl;
      exit (EXIT_FAILURE);
    }
    /* Connect to the MySQL test database */
    con_->setSchema("connectplus");
  }

  ~Sql() {
    delete con_;
    output_.close();
  }

  int InsertRegionToWechat(const std::string& uuid, const std::string& region_code) {
    /*
    std::string sql_command = "SELECT * FROM wechat_blogger_region WHERE blogger_uuid='" +
                              uuid + "' AND region_code='" + region_code + "'";
                              */
    if (uuid.size() > 20 || region_code.size() > 15)
      return -1;
    std::string sql_command;
    std::string sql_command_out = "INSERT INTO wechat_blogger_region (blogger_uuid, region_code) VALUES ('" +
                    uuid + "', '" + region_code + "')";
    output_ << sql_command_out << ";" << std::endl;
    return 0;
    int ret = 0;
    try {
      std::shared_ptr<sql::Statement> stmt(con_->createStatement());

    std::shared_ptr<sql::ResultSet> res(stmt->executeQuery(sql_command));
    if (res->next()) {
      // exist record
      return -1;
    }
    sql_command = "INSERT INTO wechat_blogger_region (blogger_uuid, region_code) VALUES ('" +
                    uuid + "', '" + region_code + "')";

    ret =  stmt->execute(sql_command);

    } catch (...) {
      std::cout << sql_command << std::endl;
      exit (EXIT_FAILURE);
    }
    return ret;
  }


private:
  sql::Driver *driver_;
  sql::Connection *con_;
  std::ofstream output_;
};


#endif
