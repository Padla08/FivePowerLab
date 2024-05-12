import java.util.*;

class Patient implements Comparable<Patient> {
    String ticket;
    int duration;

    public Patient(String ticket, int duration) {
        this.ticket = ticket;
        this.duration = duration;
    }

    @Override
    public int compareTo(Patient other) {
        // Обратите внимание на знак меньше, чтобы приоритет имел наибольшее время обслуживания
        return Integer.compare(other.duration, this.duration);
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Введите количество окон: ");
        int numWindows = scanner.nextInt();
        scanner.nextLine(); // Consume newline left-over

        PriorityQueue<Patient> allPatients = new PriorityQueue<>();
        List<PriorityQueue<Patient>> windows = new ArrayList<>();
        for (int i = 0; i < numWindows; i++) {
            windows.add(new PriorityQueue<>());
        }
        int ticketNumber = 1; // Начальный номер талона

        while (scanner.hasNext()) {
            String command = scanner.next();
            if (command.equals("ENQUEUE")) {
                int duration = scanner.nextInt();
                String ticket = "T" + (ticketNumber++);
                Patient patient = new Patient(ticket, duration);
                allPatients.add(patient);
                System.out.println("Посетитель добавлен в очередь под номером талона: " + ticket);
            } else if (command.equals("DISTRIBUTE")) {
                // Распределение посетителей по окнам
                while (!allPatients.isEmpty()) {
                    // Находим окно с наименьшей очередью
                    int minQueueIndex = 0;
                    for (int i = 1; i < numWindows; i++) {
                        if (windows.get(i).size() < windows.get(minQueueIndex).size()) {
                            minQueueIndex = i;
                        }
                    }
                    // Добавляем посетителя в очередь наименьшего размера
                    Patient patient = allPatients.poll();
                    windows.get(minQueueIndex).add(patient);
                }

                // Вывод распределения очереди посетителей на все окна
                for (int i = 0; i < numWindows; i++) {
                    System.out.print("Окно " + (i + 1) + ": ");
                    PriorityQueue<Patient> windowQueue = windows.get(i);
                    while (!windowQueue.isEmpty()) {
                        Patient patient = windowQueue.poll();
                        System.out.print(patient.ticket + " (" + patient.duration + " минут) ");
                    }
                    System.out.println();
                }
            } else if (command.equals("HELP")) {
                // Вывод справки
                System.out.println("Команды:");
                System.out.println("ENQUEUE <время обслуживания> - добавление посетителя в очередь");
                System.out.println("DISTRIBUTE - распределение очереди посетителей на все окна");
                System.out.println("HELP - вывод справки");
            } else {
                System.out.println("Неизвестная команда. Введите HELP для получения справки.");
            }
        }
    }
}