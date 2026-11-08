package org.example;

import java.util.List;

public class Main {
    public static void main(String[] args) {
        BicycleDao dao = new BicycleDao();

        dao.createTable();

        dao.insert(new Bicycle("Trek","Domane SL 5","шоссейный",224900,2023));
        dao.insert(new Bicycle("Trek","Domane AL 2","шоссейный",108000,2022));
        dao.insert(new Bicycle("Trek","Emonda ALR 5","шоссейный",171000,2023));
        dao.insert(new Bicycle("Trek","Checkpoint ALR 5","гравийный",198000,2022));
        dao.insert(new Bicycle("Trek","Boone 5","циклокросс",216000,2023));
        dao.insert(new Bicycle("Trek","Farley 5","фэтбайк",180000,2022));
        dao.insert(new Bicycle("Trek","Marlin 5","горный",67500,2023));
        dao.insert(new Bicycle("Trek","X-Caliber 8","горный",144000,2022));
        dao.insert(new Bicycle("Trek","Roscoe 7","горный",126000,2023));
        dao.insert(new Bicycle("Trek","Fuel EX 5","горный",252000,2022));
        dao.insert(new Bicycle("Specialized","Allez Sport","шоссейный",108000,2023));
        dao.insert(new Bicycle("Specialized","Tarmac SL6","шоссейный",288000,2022));
        dao.insert(new Bicycle("Specialized","Roubaix Sport","шоссейный",252000,2023));
        dao.insert(new Bicycle("Specialized","Diverge E5","гравийный",126000,2022));
        dao.insert(new Bicycle("Specialized","CruX Sport","циклокросс",180000,2023));
        dao.insert(new Bicycle("Specialized","Rockhopper Comp","горный",85500,2022));
        dao.insert(new Bicycle("Specialized","Chisel Comp","горный",171000,2023));
        dao.insert(new Bicycle("Specialized","Stumpjumper Alloy","горный",234000,2022));
        dao.insert(new Bicycle("Specialized","Fuse 27.5","горный",135000,2023));
        dao.insert(new Bicycle("Giant","Contend AR 3","шоссейный",121500,2022));
        dao.insert(new Bicycle("Giant","TCR Advanced 2","шоссейный",234000,2023));
        dao.insert(new Bicycle("Giant","Defy Advanced 3","шоссейный",207000,2022));
        dao.insert(new Bicycle("Giant","Revolt 1","гравийный",162000,2023));
        dao.insert(new Bicycle("Giant","TCX SLR 2","циклокросс",171000,2022));
        dao.insert(new Bicycle("Giant","Talon 2","горный",63000,2023));
        dao.insert(new Bicycle("Giant","Stance 2","горный",144000,2022));
        dao.insert(new Bicycle("Giant","Trance X 3","горный",225000,2023));
        dao.insert(new Bicycle("Cannondale","Synapse Carbon 3","шоссейный",288000,2022));
        dao.insert(new Bicycle("Cannondale","CAAD13 105","шоссейный",198000,2023));
        dao.insert(new Bicycle("Cannondale","Topstone 1","гравийный",189000,2022));

        for (Bicycle bike : dao.getAll()) {
            System.out.println(bike);
        }
    }
}