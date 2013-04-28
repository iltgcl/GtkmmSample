#ifndef MVC_INTERFACE_H
#define MVC_INTERFACE_H

#define Interface   class
#define implements  public

#define DECLARE_INTERFACE(name) Interface name { \
          public: \
           virtual ~name() {}

#define END_INTERFACE(name) };

#define DECLARE_BASED_INTERFACE(name, base) class name : public base { \
          public: \
           virtual ~name() {}

/* forward declare */
Interface IView;
Interface IModel;
Interface IController;

class Request;

/* define interfaces */
DECLARE_INTERFACE(IView)
  virtual void request(const Request *req) = 0;
  virtual IController& getController() = 0;
  virtual void onCmdStateChanged() = 0;
  virtual void onModelChanged() = 0;
END_INTERFACE(IView)

DECLARE_INTERFACE(IMODEL)
  virtual void addListener(IView* view) = 0;
  virtual void handleRequest(Request *req) = 0;
END_INTERFACE(IMODEL)

DECLARE_INTERFACE(IController)
  virtual void addModel(int index, IModel* model) = 0;
  virtual IModel* getModel(int index) = 0;
  virtual void request(const Request *req) = 0;
END_INTERFACE(IController)



#endif /* MVC_INTERFACE_H */
