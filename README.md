# FUT_LAB_arduino_door_lock

You need wifi, arduino, servo and a simple website.

You need some tables in database (website, backend):

```
users (id(int), username(varchar), password(varchar/hash))
doors (id(int), hash(varchar), door_name(varchar), is_open(boolean))
doors_history (id(int), door_id(int), user_id(int), action(boolean, 1:unlock, 0:lock))
```

You must have an URL something like ```http://{WEBSITE}/check/{DOOR_HASH}```
Server takes hash from query string, selects from database door with the given hash and 
returns the door's current status (1 if door is unlocked, 0 if is locked)

You need to implement simple login form in your website.
When user is logged, you must show him/her lock/unlock buttons and history from database.

Lock/unlock action is not difficult. You must change the door's status (is_open, 1 or 0) and insert
this action in doors_history.

More info: https://lab-doors.blogspot.com/
