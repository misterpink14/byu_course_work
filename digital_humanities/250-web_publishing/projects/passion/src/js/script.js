var data = {
	"Command" : {
		"problem" : "Need to issue requests to objects without knowing anything about the operation being requested or the receiver of the request.",
		"discussion" : 'Command decouples the object that invokes the operation from the one that knows how to perform it. To achieve this separation, the designer creates an abstract base class that maps a receiver (an object) with an action (a pointer to a member function). The base class contains an execute() method that simply calls the action on the receiver.<br /><br />All clients of Command objects treat each object as a "black box" by simply invoking the object\'s virtual execute() method whenever the client requires the object\'s "service".<br /><br />A Command class holds some subset of the following: an object, a method to be applied to the object, and the arguments to be passed when the method is applied. The Command\'s "execute" method then causes the pieces to come together.<br /><br />Sequences of Command objects can be assembled into composite (or macro) commands.'
	},
	"State" : {
		"problem" : "A monolithic object's behavior is a function of its state, and it must change its behavior at run-time depending on that state. Or, an application is characterixed by large and numerous case statements that vector flow of control based on the state of the application.",
		"discussion" : "The State pattern is a solution to the problem of how to make behavior depend on state.<br /><br />Define a \"context\" class to present a single interface to the outside world.<br />Define a State abstract base class.<br />Represent the different \"states\" of the state machine as derived classes of the State base class.<br />Define state-specific behavior in the appropriate State derived classes.<br />Maintain a pointer to the current \"state\" in the \"context\" class.<br />To change the state of the state machine, change the current \"state\" pointer.<br />The State pattern does not specify where the state transitions will be defined. The choices are two: the \"context\" object, or each individual State derived class. The advantage of the latter option is ease of adding new State derived classes. The disadvantage is each State derived class has knowledge of (coupling to) its siblings, which introduces dependencies between subclasses.<br /><br />A table-driven approach to designing finite state machines does a good job of specifying state transitions, but it is difficult to add actions to accompany the state transitions. The pattern-based approach uses code (instead of data structures) to specify state transitions, but it does a good job of accomodating state transition actions.",
	},
	"Strategy" : {
		"problem" : "An aspect of a class needs to be customized by the object that is calling it.",
		"discussion" : "A Strategy defines a set of algorithms that can be used interchangeably. Modes of transportation to an airport is an example of a Strategy. Several options exist such as driving one's own car, taking a taxi, an airport shuttle, a city bus, or a limousine service. For some airports, subways and helicopters are also available as a mode of transportation to the airport. Any of these modes of transportation will get a traveler to the airport, and they can be used interchangeably. The traveler must chose the Strategy based on tradeoffs between cost, convenience, and time.",
	},
	"Template Method" : {
		"problem" : "Two different components have significant similarities, but demonstrate no reuse of common interface or implementation. If a change common to both components becomes necessary, duplicate effort must be expended.",
		"discussion" : "The component designer decides which steps of an algorithm are invariant (or standard), and which are variant (or customizable). The invariant steps are implemented in an abstract base class, while the variant steps are either given a default implementation, or no implementation at all. The variant steps represent \"hooks\", or \"placeholders\", that can, or must, be supplied by the component's client in a concrete derived class.<br/><br/>The component designer mandates the required steps of an algorithm, and the ordering of the steps, but allows the component client to extend or replace some number of these steps.<br/><br/>Template Method is used prominently in frameworks. Each framework implements the invariant pieces of a domain's architecture, and defines \"placeholders\" for all necessary or interesting client customization options. In so doing, the framework becomes the \"center of the universe\", and the client customizations are simply \"the third rock from the sun\". This inverted control structure has been affectionately labelled \"the Hollywood principle\" - \"don't call us, we'll call you\".",
	},
	"Factory Method" : {
		"problem" : "A framework needs to standardize the architectural model for a range of applications, but allow for individual applications to define their own domain objects and provide for their instantiation.",
		"discussion" : "Factory Method is to creating objects as Template Method is to implementing an algorithm. A superclass specifies all standard and generic behavior (using pure virtual \"placeholders\" for creation steps), and then delegates the creation details to subclasses that are supplied by the client.<br/><br/>Factory Method makes a design more customizable and only a little more complicated. Other design patterns require new classes, whereas Factory Method only requires a new operation.<br/><br/>People often use Factory Method as the standard way to create objects; but it isn't necessary if: the class that's instantiated never changes, or instantiation takes place in an operation that subclasses can easily override (such as an initialization operation).<br/><br/>Factory Method is similar to Abstract Factory but without the emphasis on families.<br/><br/>Factory Methods are routinely specified by an architectural framework, and then implemented by the user of the framework.",
	},
	"Singleton" : {
		"problem" : "Application needs one, and only one, instance of an object. Additionally, lazy initialization and global access are necessary.",
		"discussion" : "Make the class of the single instance object responsible for creation, initialization, access, and enforcement. Declare the instance as a private static data member. Provide a public static member function that encapsulates all initialization code, and provides access to the instance.<br/><br/>The client calls the accessor function (using the class name and scope resolution operator) whenever a reference to the single instance is required.<br/><br/>Singleton should be considered only if all three of the following criteria are satisfied:<br/><br/>Ownership of the single instance cannot be reasonably assigned<br/>Lazy initialization is desirable<br/>Global access is not otherwise provided for<br/><br/>If ownership of the single instance, when and how initialization occurs, and global access are not issues, Singleton is not sufficiently interesting.<br/><br/>The Singleton pattern can be extended to support access to an application-specific number of instances.<br/><br/>The \"static member function accessor\" approach will not support subclassing of the Singleton class. If subclassing is desired, refer to the discussion in the book.<br/><br/>Deleting a Singleton class/instance is a non-trivial design problem. See \"To Kill A Singleton\" by John Vlissides for a discussion.",
	},
	"Abstract Factory" : {
		"problem" : "If an application is to be portable, it needs to encapsulate platform dependencies. These \"platforms\" might include: windowing system, operating system, database, etc. Too often, this encapsulatation is not engineered in advance, and lots of #ifdef case statements with options for all currently supported platforms begin to procreate like rabbits throughout the code.",
		"discussion" : "Provide a level of indirection that abstracts the creation of families of related or dependent objects without directly specifying their concrete classes. The \"factory\" object has the responsibility for providing creation services for the entire platform family. Clients never create platform objects directly, they ask the factory to do that for them.<br/><br/>This mechanism makes exchanging product families easy because the specific class of the factory object appears only once in the application - where it is instantiated. The application can wholesale replace the entire family of products simply by instantiating a different concrete instance of the abstract factory.<br/><br/>Because the service provided by the factory object is so pervasive, it is routinely implemented as a Singleton.",
	},
	"Decorator" : {
		"problem" : "You want to add behavior or state to individual objects at run-time. Inheritance is not feasible because it is static and applies to an entire class.",
		"discussion" : "The solution to this class of problems involves encapsulating the original object inside an abstract wrapper interface. Both the decorator objects and the core object inherit from this abstract interface. The interface uses recursive composition to allow an unlimited number of decorator \"layers\" to be added to each core object.<br/><br/>Note that this pattern allows responsibilities to be added to an object, not methods to an object's interface. The interface presented to the client must remain constant as successive layers are specified.<br/><br/>Also note that the core object's identity has now been \"hidden\" inside of a decorator object. Trying to access the core object directly is now a problem.",
	},
	"Proxy" : {
		"problem" : "You need to support resource-hungry objects, and you do not want to instantiate such objects unless and until they are actually requested by the client.",
		"discussion" : "Design a surrogate, or proxy, object that: instantiates the real object the first time the client makes a request of the proxy, remembers the identity of this real object, and forwards the instigating request to this real object. Then all subsequent requests are simply forwarded directly to the encapsulated real object.",
	},
	"Adapter" : {
		"problem" : "An \"off the shelf\" component offers compelling functionality that you would like to reuse, but its \"view of the world\" is not compatible with the philosophy and architecture of the system currently being developed.",
		"discussion" : "Reuse has always been painful and elusive. One reason has been the tribulation of designing something new, while reusing something old. There is always something not quite right between the old and the new. It may be physical dimensions or misalignment. It may be timing or synchronization. It may be unfortunate assumptions or competing standards.<br/><br/>It is like the problem of inserting a new three-prong electrical plug in an old two-prong wall outlet – some kind of adapter or intermediary is necessary.<br/><br/>Adapter is about creating an intermediary abstraction that translates, or maps, the old component to the new system. Clients call methods on the Adapter object which redirects them into calls to the legacy component. This strategy can be implemented either with inheritance or with aggregation.<br/><br/>Adapter functions as a wrapper or modifier of an existing class. It provides a different or translated view of that class.",
	}
}


var patternBtn = document.getElementsByClassName("pattern");



[].forEach.call(patternBtn, function (element) {
	element.addEventListener(
		"click", 
		function(){ 
			var text = this.innerHTML.trim();
			var problemElement = document.getElementById("problem");
			var discussionElement = document.getElementById("discussion");
			problemElement.innerHTML = data[text].problem
			discussionElement.innerHTML = data[text].discussion
		}
	);
	element.addEventListener(
		"click", 
		function(){ 
			var show = document.getElementsByClassName("click-to-show");
			[].forEach.call(show, function (element) {
				element.style.display = 'block';
			})
		}
	);
})
