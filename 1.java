import java.util.*;

class Item {
    String name;
    int quantity;

    Item(String name, int quantity) {
        this.name = name;
        this.quantity = quantity;
    }
}

class Warehouse {
    private Map<String, Item[][][]> warehouse;
    private int totalCapacity;
    private int usedCapacity;
    private int maxItemQuantity;

    Warehouse(int zones, int racks, int shelves, int cells, int totalCapacity, int maxItemQuantity) {
        this.totalCapacity = totalCapacity;
        this.maxItemQuantity = maxItemQuantity;
        usedCapacity = 0;
        warehouse = new HashMap<>();

        for (char zone = 'A'; zone < 'A' + zones; ++zone) {
            Item[][][] rackArr = new Item[racks][][];
            for (int rack = 0; rack < racks; ++rack) {
                Item[][] shelfArr = new Item[shelves][];
                for (int shelf = 0; shelf < shelves; ++shelf) {
                    Item[] cellArr = new Item[cells];
                    for (int cell = 0; cell < cells; ++cell) {
                        cellArr[cell] = new Item("", 0);
                    }
                    shelfArr[shelf] = cellArr;
                }
                rackArr[rack] = shelfArr;
            }
            warehouse.put(String.valueOf(zone), rackArr);
        }
    }

    void addItem(String name, int quantity, String address) {
    if (address.length() != 4) {
        System.out.println("Invalid cell address. Address should be in the format A111.");
        return;
    }

    char zone = address.charAt(0);
    int rack, shelf, cell;

    try {
        rack = Integer.parseInt(address.substring(1, 3)) - 1;
        shelf = address.charAt(2) - '1'; // Convert char to int and subtract 1
        cell = address.charAt(3) - '1'; // Convert char to int and subtract 1
    } catch (NumberFormatException e) {
        System.out.println("Invalid cell address. Address should be in the format A111.");
        return;
    }

        Item item = warehouse.get(String.valueOf(zone))[rack][shelf][cell];
        if (!item.name.isEmpty() && !item.name.equals(name)) {
            System.out.println("Cell already contains an item. Remove it first or use a different cell.");
            return;
        }
        if (usedCapacity + quantity > totalCapacity || item.quantity + quantity > maxItemQuantity) {
            System.out.println("Not enough space to add the item.");
            return;
        }
        item.name = name;
        item.quantity += quantity;
        usedCapacity += quantity;
    }

    void removeItem(String name, int quantity, String address) {
    if (address.length() != 4) {
        System.out.println("Invalid cell address. Address should be in the format A111.");
        return;
    }

    char zone = address.charAt(0);
    int rack, shelf, cell;

    try {
        rack = Integer.parseInt(address.substring(1, 3)) - 1;
        shelf = address.charAt(2) - '1'; // Convert char to int and subtract 1
        cell = address.charAt(3) - '1'; // Convert char to int and subtract 1
    } catch (NumberFormatException e) {
        System.out.println("Invalid cell address. Address should be in the format A111.");
        return;
    }

    Item item = warehouse.get(String.valueOf(zone))[rack][shelf][cell];
    if (!item.name.equals(name)) {
        System.out.println("Cell does not contain the specified item.");
        return;
    }
    if (item.quantity < quantity) {
        System.out.println("Not enough items in the cell to remove.");
        return;
    }
    item.quantity -= quantity;
    usedCapacity -= quantity;
    if (item.quantity == 0) {
        item.name = "";
    }
}

    void info() {
        System.out.println("Warehouse usage: " + (usedCapacity * 100.0) / totalCapacity + "%");

        for (Map.Entry<String, Item[][][]> entry : warehouse.entrySet()) {
            int zoneUsedCapacity = 0;
            for (Item[][] rack : entry.getValue()) {
                for (Item[] shelf : rack) {
                    for (Item cell : shelf) {
                        zoneUsedCapacity += cell.quantity;
                    }
                }
            }
            System.out.println("Zone " + entry.getKey() + " usage: " + (zoneUsedCapacity * 100.0) / totalCapacity + "%");
        }

        for (Map.Entry<String, Item[][][]> entry : warehouse.entrySet()) {
            for (int rack = 0; rack < entry.getValue().length; ++rack) {
                for (int shelf = 0; shelf < entry.getValue()[rack].length; ++shelf) {
                    for (int cell = 0; cell < entry.getValue()[rack][shelf].length; ++cell) {
                        Item item = entry.getValue()[rack][shelf][cell];
                        if (item.quantity > 0) {
                            System.out.println(entry.getKey() + (rack + 1) + (shelf + 1) + (cell + 1) + ": " + item.name + " - " + item.quantity);
                        }
                    }
                }
            }
        }
    }

    void processCommand(String command) {
        Scanner scanner = new Scanner(command);
        String action = scanner.next();

        switch (action) {
            case "ADD":
                String name = scanner.next();
                int quantity = scanner.nextInt();
                String address = scanner.next();
                addItem(name, quantity, address);
                break;
            case "REMOVE":
                name = scanner.next();
                quantity = scanner.nextInt();
                address = scanner.next();
                removeItem(name, quantity, address);
                break;
            case "INFO":
                info();
                break;
            case "HELP":
                displayHelp();
                break;
            case "EXIT":
                System.exit(0);
                break;
            default:
                System.out.println("Unknown command. Type HELP for available commands.");
        }
        scanner.close();
    }

    void displayHelp() {
        System.out.println("Available commands:");
        System.out.println("ADD <item name> <quantity> <cell address> - Add items to the specified cell.");
        System.out.println("REMOVE <item name> <quantity> <cell address> - Remove items from the specified cell.");
        System.out.println("INFO - Display warehouse information.");
        System.out.println("HELP - Display this help message.");
        System.out.println("EXIT - Exit the program.");
    }
}

public class Main {
    public static void main(String[] args) {
        Warehouse warehouse = new Warehouse(3, 20, 5, 2, 6000, 100);

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter command (type HELP for help):");
        while (scanner.hasNextLine()) {
            warehouse.processCommand(scanner.nextLine());
            System.out.println("Enter command (type HELP for help):");
        }
        scanner.close();
    }
}