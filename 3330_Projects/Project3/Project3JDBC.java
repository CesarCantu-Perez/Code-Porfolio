import java.sql.*;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Project3JDBC {
    public static void main(String[] args){
        int open = 1;
        int ID = 0;
        int choice = 0;
        String pilotName = "";
        Scanner scanner = new Scanner(System.in);
        while(open == 1){

            System.out.println("Choose a Menu option:");
            System.out.println("1. List Pilots");
            System.out.println("2. List Airports");
            System.out.println("3. Add Pilot");
            System.out.println("4. Quit");
            System.out.print("Please enter the number corresponding to the option you want to choose : ");
            try{
                choice = scanner.nextInt();
            }catch(InputMismatchException msg){
                System.out.println("Input Mismatch Exception has occurred.");
            }

            if(choice == 1){
                System.out.println("List of available Pilots: ");
                try{
                    Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/newschema", "root", "Carrillo2!");
                    Statement statement = connection.createStatement();
                    ResultSet resultSet = statement.executeQuery("select ID, Name, DateHired from Pilot");

                    while(resultSet.next())
                    {
                        System.out.print(resultSet.getString("ID"));
                        System.out.print("  ");
                        System.out.print(resultSet.getString("Name"));
                        System.out.print("  ");
                        System.out.print(resultSet.getString("DateHired"));
                        System.out.println("");
                    }
                } catch(Exception e){
                    e.printStackTrace();
                }
            }
            else if(choice == 2){
                System.out.println("List of available Pilots");
                try{
                    Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/newschema", "root", "Carrillo2!");
                    Statement statement = connection.createStatement();
                    ResultSet resultSet = statement.executeQuery("select Code, City, State from Airport");
                    while(resultSet.next())
                    {
                        System.out.print(resultSet.getString("Code"));
                        System.out.print("  ");
                        System.out.print(resultSet.getString("City"));
                        System.out.print("  ");
                        System.out.print(resultSet.getString("State"));
                        System.out.println("");
                    }
                } catch(Exception e){
                    e.printStackTrace();
                }
            }
            else if(choice == 3){
                System.out.print("Name?:");
                pilotName = scanner.next();
                String quitPrompt = "/q";
                int nameMatch = 1;
                if(quitPrompt.equals(pilotName)){
                    System.out.println("Returning to menu...");
                }
                else {
                    try {
                        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/newschema", "root", "Carrillo2!");
                        Statement statement = connection.createStatement();
                        ResultSet resultSet = statement.executeQuery("select ID, Name from Pilot");

                        while (resultSet.next()) {
                            String name = resultSet.getString("Name");
                            ID = resultSet.getInt("ID");
                            if (pilotName.equals(name)) {
                                nameMatch = 0;
                            }
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    if (nameMatch == 1) {
                        ID = ID + 1;
                        long today = System.currentTimeMillis();
                        java.sql.Date dateHired = new java.sql.Date(today);
                        try {
                            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/newschema", "root", "Carrillo2!");
                            Statement statement = connection.createStatement();
                            String sql = "insert into Pilot " + " (ID, Name, DateHired)" + " values (?, ?, ?)";
                            statement = connection.prepareStatement(sql);
                            ((PreparedStatement) statement).setInt(1, ID);
                            ((PreparedStatement) statement).setString(2, pilotName);
                            ((PreparedStatement) statement).setDate(3, dateHired);
                            ((PreparedStatement) statement).executeUpdate();
                            System.out.println("Pilot added");
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    } else {
                        System.out.println("There is a Pilot with this name");
                    }
                }
            }
            else if(choice == 4){
                open = 0;
            }
            else{
                System.out.println("Please select a choice from the menu (1-4).");
            }
        }

    }
}
