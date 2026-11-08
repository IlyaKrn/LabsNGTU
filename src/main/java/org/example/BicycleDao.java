package org.example;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class BicycleDao {

    private final String url = "jdbc:h2:mem:database;DB_CLOSE_DELAY=-1";
    private final String user = "user";
    private final String password = "";

    public void createTable() throws SQLException {
        String sql = "CREATE TABLE IF NOT EXISTS bicycles (" +
                "id INT PRIMARY KEY AUTO_INCREMENT, " +
                "brand VARCHAR(255), " +
                "model VARCHAR(255), " +
                "category VARCHAR(255), " +
                "price INT, " +
                "release_year INT)";

        Connection conn = DriverManager.getConnection(url, user, password);
        Statement stmt = conn.createStatement();
        stmt.execute(sql);
    }

    // 1. ДОБАВЛЕНИЕ ЭЛЕМЕНТА (пункт 2 из задания)
    public void insert(Bicycle bicycle) throws SQLException {
        String sql = "INSERT INTO bicycles (brand, model, category, price, release_year) VALUES (?, ?, ?, ?, ?)";

        Connection conn = DriverManager.getConnection(url, user, password);
        PreparedStatement pstmt = conn.prepareStatement(sql);

        pstmt.setString(1, bicycle.getBrand());
        pstmt.setString(2, bicycle.getModel());
        pstmt.setString(3, bicycle.getCategory());
        pstmt.setInt(4, bicycle.getPrice());
        pstmt.setInt(5, bicycle.getReleaseYear());

        pstmt.executeUpdate();
    }

    public List<Bicycle> getAll() throws SQLException {
        List<Bicycle> bicycles = new ArrayList<>();
        String sql = "SELECT * FROM bicycles";

        Connection conn = DriverManager.getConnection(url, user, password);
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery(sql);
        while (rs.next()) {
            Bicycle bike = new Bicycle(
                    rs.getInt("id"),
                    rs.getString("brand"),
                    rs.getString("model"),
                    rs.getString("category"),
                    rs.getInt("price"),
                    rs.getInt("release_year")
            );
            bicycles.add(bike);
        }
        return bicycles;
    }
}