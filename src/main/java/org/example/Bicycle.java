package org.example;

public class Bicycle {
    private int id;
    private String brand;
    private String model;
    private String category;
    private int price;
    private int releaseYear;


    public Bicycle(int id, String brand, String model, String category, int price, int releaseYear) {
        this.id = id;
        this.brand = brand;
        this.model = model;
        this.category = category;
        this.price = price;
        this.releaseYear = releaseYear;
    }

    public Bicycle(String brand, String model, String category, int price, int releaseYear) {
        this.brand = brand;
        this.model = model;
        this.category = category;
        this.price = price;
        this.releaseYear = releaseYear;
    }

    public int getId() {return id;}
    public String getBrand() {return brand;}
    public String getModel() {return model;}
    public String getCategory() {return category;}
    public int getPrice() {return price;}
    public int getReleaseYear() {return releaseYear;}

    @Override
    public String toString() {
        return "Bicycle{" +
                "id=" + id +
                ", brand='" + brand + '\'' +
                ", model='" + model + '\'' +
                ", category='" + category + '\'' +
                ", price=" + price +
                ", releaseYear=" + releaseYear +
                '}';
    }
}