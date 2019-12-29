/*
// A Java program to demonstrate implementation 
// of iterator pattern with the example of 
// notifications 

// A simple Notification class 
class Notification 
{ 
	// To store notification message 
	String notification; 

	public Notification(String notification) 
	{ 
		this.notification = notification; 
	} 
	public String getNotification() 
	{ 
		return notification; 
	} 
} 

// Collection interface 
interface Collection 
{ 
	public Iterator createIterator(); 
} 

// Collection of notifications 
class NotificationCollection implements Collection 
{ 
	static final int MAX_ITEMS = 6; 
	int numberOfItems = 0; 
	Notification[] notificationList; 

	public NotificationCollection() 
	{ 
		notificationList = new Notification[MAX_ITEMS]; 

		// Let us add some dummy notifications 
		addItem("Notification 1"); 
		addItem("Notification 2"); 
		addItem("Notification 3"); 
	} 

	public void addItem(String str) 
	{ 
		Notification notification = new Notification(str); 
		if (numberOfItems >= MAX_ITEMS) 
			System.err.println("Full"); 
		else
		{ 
			notificationList[numberOfItems] = notification; 
			numberOfItems = numberOfItems + 1; 
		} 
	} 

	public Iterator createIterator() 
	{ 
		return new NotificationIterator(notificationList); 
	} 
} 

// We could also use Java.Util.Iterator 
interface Iterator 
{ 
	// indicates whether there are more elements to 
	// iterate over 
	boolean hasNext(); 

	// returns the next element 
	Object next(); 
} 

// Notification iterator 
class NotificationIterator implements Iterator 
{ 
	Notification[] notificationList; 

	// maintains curr pos of iterator over the array 
	int pos = 0; 

	// Constructor takes the array of notifiactionList are 
	// going to iterate over. 
	public NotificationIterator (Notification[] notificationList) 
	{ 
		this.notificationList = notificationList; 
	} 

	public Object next() 
	{ 
		// return next element in the array and increment pos 
		Notification notification = notificationList[pos]; 
		pos += 1; 
		return notification; 
	} 

	public boolean hasNext() 
	{ 
		if (pos >= notificationList.length || 
			notificationList[pos] == null) 
			return false; 
		else
			return true; 
	} 
} 

// Contains collection of notifications as an object of 
// NotificationCollection 
class NotificationBar 
{ 
	NotificationCollection notifications; 

	public NotificationBar(NotificationCollection notifications) 
	{ 
		this.notifications = notifications; 
	} 

	public void printNotifications() 
	{ 
		Iterator iterator = notifications.createIterator(); 
		System.out.println("-------NOTIFICATION BAR------------"); 
		while (iterator.hasNext()) 
		{ 
			Notification n = (Notification)iterator.next(); 
			System.out.println(n.getNotification()); 
		} 
	} 
} 

// Driver class 
class Main 
{ 
	public static void main(String args[]) 
	{ 
		NotificationCollection nc = new NotificationCollection(); 
		NotificationBar nb = new NotificationBar(nc); 
		nb.printNotifications(); 
	} 
} 
*/

int main()
{

}
