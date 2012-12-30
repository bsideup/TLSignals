TLSignals
=========

Signals for Objective-C++

Example
=========

Let me show you how it's easy to observe some object for notifications using TLSignal. For example, we've ExampleViewController, and we would like to know when his view is loaded:
ExampleViewController.mm
---------
```objective-c
#import "Signals.h"

@interface ExampleViewController : UIViewController

@property (nonatomic, readonly) TLSignal<UIView *> *viewDidLoadSignal;

@end

@implementation ExampleViewController

tl_synthesize_signal(viewDidLoadSignal, UIView *);

-(void)viewDidLoad
{
    [super viewDidLoad];
    // Notifying watchers about viewDidLoad event
    self.viewDidLoadSignal->notify(self.view);
}

@end
```
Easy, huh?

AppDelegate.mm
---------
```objective-c
#import "AppDelegate.h"
#import "ExampleViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)options
{
    UIWindow window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.viewController = [[ExampleViewController alloc] initWithNibName:@"ExampleViewController" bundle:nil];
    
    // Subscribe to our event
    self.viewController.viewDidLoadSignal->addObserver(^(TLSignal<UIView *> *signal, UIView *targetView)
    {
        targetView.backgroundColor = [UIColor blackColor];
    });
    
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    return YES;
}

@end

```



License
=========
Licensed under the MIT license
