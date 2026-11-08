package org.example;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Main {

    private static final String url = "jdbc:h2:mem:database";
    private static final String user = "user";
    private static final String password = "";

    public static void main(String[] args) {

        try (Connection connection = DriverManager.getConnection(url, user, password); Statement statement = connection.createStatement()) {

            //таблица
            statement.execute("CREATE TABLE bicycles (" +
                    "id INT PRIMARY KEY AUTO_INCREMENT, " +
                    "brand  VARCHAR(255), " +
                    "model  VARCHAR(255), " +
                    "category  VARCHAR(255), " +
                    "price INT," +
                    "release_year INT" +
                    ");"
            );

            //загрузка данных
            statement.execute("INSERT INTO bicycles (brand,model,category,price,release_year) VALUES " +
                    "('Trek','Domane SL 5','шоссейный',224900,2023)," +
                    "('Trek','Domane AL 2','шоссейный',108000,2022)," +
                    "('Trek','Emonda ALR 5','шоссейный',171000,2023)," +
                    "('Trek','Checkpoint ALR 5','гравийный',198000,2022)," +
                    "('Trek','Boone 5','циклокросс',216000,2023)," +
                    "('Trek','Farley 5','фэтбайк',180000,2022)," +
                    "('Trek','Marlin 5','горный',67500,2023)," +
                    "('Trek','X-Caliber 8','горный',144000,2022)," +
                    "('Trek','Roscoe 7','горный',126000,2023)," +
                    "('Trek','Fuel EX 5','горный',252000,2022)," +
                    "('Specialized','Allez Sport','шоссейный',108000,2023)," +
                    "('Specialized','Tarmac SL6','шоссейный',288000,2022)," +
                    "('Specialized','Roubaix Sport','шоссейный',252000,2023)," +
                    "('Specialized','Diverge E5','гравийный',126000,2022)," +
                    "('Specialized','CruX Sport','циклокросс',180000,2023)," +
                    "('Specialized','Rockhopper Comp','горный',85500,2022)," +
                    "('Specialized','Chisel Comp','горный',171000,2023)," +
                    "('Specialized','Stumpjumper Alloy','горный',234000,2022)," +
                    "('Specialized','Fuse 27.5','горный',135000,2023)," +
                    "('Giant','Contend AR 3','шоссейный',121500,2022)," +
                    "('Giant','TCR Advanced 2','шоссейный',234000,2023)," +
                    "('Giant','Defy Advanced 3','шоссейный',207000,2022)," +
                    "('Giant','Revolt 1','гравийный',162000,2023)," +
                    "('Giant','TCX SLR 2','циклокросс',171000,2022)," +
                    "('Giant','Talon 2','горный',63000,2023)," +
                    "('Giant','Stance 2','горный',144000,2022)," +
                    "('Giant','Trance X 3','горный',225000,2023)," +
                    "('Cannondale','Synapse Carbon 3','шоссейный',288000,2022)," +
                    "('Cannondale','CAAD13 105','шоссейный',198000,2023)," +
                    "('Cannondale','Topstone 1','гравийный',189000,2022);"
            );

            ResultSet rs = statement.executeQuery("SELECT * FROM bicycles");
            System.out.println("\nid\t brand\t model\t category\t price\t release_year");
            while (rs.next()) {
                System.out.println(rs.getInt("id") + "\t" + rs.getString("brand") + "\t" + rs.getString("model") + "\t" + rs.getString("category") + "\t" + rs.getInt("price") + "\t" + rs.getInt("release_year"));
            }
            rs.close();

            ResultSet rs1 = statement.executeQuery("SELECT DISTINCT category FROM bicycles WHERE brand = 'Trek'");
            System.out.println("\ncategory");
            while (rs1.next()) {
                System.out.println(rs1.getString("category"));
            }
            rs1.close();

            ResultSet rs2 = statement.executeQuery("SELECT * FROM bicycles WHERE category = 'горный'");
            System.out.println("\nid\t brand\t model\t category\t price\t release_year");
            while (rs2.next()) {
                System.out.println(rs2.getInt("id") + "\t" + rs2.getString("brand") + "\t" + rs2.getString("model") + "\t" + rs2.getString("category") + "\t" + rs2.getInt("price") + "\t" + rs2.getInt("release_year"));
            }
            rs2.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}