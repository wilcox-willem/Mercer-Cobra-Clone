is_in_class(toby, csc380). /* Fact  1 */
is_in_class(bob, csc480). /* Fact  2 */
is_in_class(toby, csc480). /* Fact  3 */
is_in_class(will, csc380). /* Fact  4 */
is_in_class(will, csc325). /* Fact  5 */
is_in_class(will, csc460). /* Fact  6 */


is_in_room(csc480, wsc100). /* Fact  7 */
is_in_room(csc380, wsc238). /* Fact  8 */
is_in_room(csc325, wsc212). /* Fact  9 */
is_in_room(csc460, wsc213). /* Fact  10 */

has_temperature(wsc100, 65). /* Fact  11 */
has_temperature(wsc238, 92). /* Fact  12 */
has_temperature(wsc212, 72). /* Fact  13 */
has_temperature(wsc213, 95). /* Fact  14 */

is_hot(Person) :-
	is_in_class(Person, _),
	is_in_room(_, _),
	has_temperature(_, Temp),
	Temp > 80.

