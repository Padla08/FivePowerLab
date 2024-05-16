import java.util.*;

public class FriendshipSystem {
    private Map<String, Set<String>> friends = new HashMap<>();

    public void addFriendship(String i, String j) {
        friends.computeIfAbsent(i, k -> new HashSet<>()).add(j);
        friends.computeIfAbsent(j, k -> new HashSet<>()).add(i);
    }

    public String countFriends(String i) {
        return String.valueOf(friends.getOrDefault(i, Collections.emptySet()).size());
    }

    public boolean areFriends(String i, String j) {
        return friends.getOrDefault(i, Collections.emptySet()).contains(j);
    }

    public static void main(String[] args) {
        FriendshipSystem system = new FriendshipSystem();
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNext()) {
            String command = scanner.next();
            if (command.equals("FRIENDS")) {
                String i = scanner.next();
                String j = scanner.next();
                system.addFriendship(i, j);
            } else if (command.equals("COUNT")) {
                String i = scanner.next();
                System.out.println(system.countFriends(i));
            } else if (command.equals("QUESTION")) {
                String i = scanner.next();
                String j = scanner.next();
                System.out.println(system.areFriends(i, j) ? "YES" : "NO");
            }
        }

        scanner.close();
    }
}