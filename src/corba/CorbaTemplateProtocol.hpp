#ifndef ORO_CORBA_TEMPATE_PROTOCOL_HPP
#define ORO_CORBA_TEMPATE_PROTOCOL_HPP

#include "../Types.hpp"
#include "ExpressionProxy.hpp"

#include "CorbaPort.hpp"
#include "CorbaDataObjectProxy.hpp"
#include "CorbaBufferProxy.hpp"
#include "ExpressionServer.hpp"
#include "DataFlowI.h"
#include "corba/Services.hpp"

namespace RTT
{ namespace detail
  {
      using namespace RTT::Corba;

      /**
       * For each transportable type T, specify the conversion functions.
       *
       * @warning
       * * * * B I G  N O T E * * * *
       * This class uses the TypeTransport of Orocos which uses (void*) for
       * passing on data. TAO's CORBA implementation uses virtual inheritance,
       * which does not work well together with (void*). That is, you must cast
       * back to the exect same type the (void*) originated from and NOT to a 
       * sub- or super-class. That would have been allowed without virtual inheritance.
       * @warning
       * Hence, this class uses always the same base class (Expression_ptr) to
       * communicate with the TypeTransport interface. Such that we know that when
       * we receive a (void*) it came from an (Expression_ptr) and vice versa.
       * @warning
       * Don't obey this and you'll get immediate hard to dissect crashes !
       * * * * B I G  N O T E * * * *
       */
      template<class T>
      class CorbaTemplateProtocol
          : public TypeTransporter
      {
      public:
          /**
           * The given \a T parameter is the type for reading DataSources.
           */
          typedef T UserType;
          /**
           * When Properties of \a T are constructed, they are non-const, non-reference.
           */
          typedef typename Property<T>::DataSourceType PropertyType;

          /**
           * Create an transportable object for a \a protocol which contains the value of \a source.
           */
          virtual void* createBlob( DataSourceBase::shared_ptr source) const
          {
              DataSource<T>* d = AdaptDataSource<T>()( source );
              if ( d )
                  return AnyConversion<PropertyType>::createAny( d->value() );
              return 0;
          }

          /**
           * Update \a target with the contents of \a blob which is an object of a \a protocol.
           */
          virtual bool updateBlob(const void* blob, DataSourceBase::shared_ptr target) const 
          {
            //This line causes a compile error in DataSourceAdaptor.hpp (where the bug is)
            //Only narrow.
//             AssignableDataSource<T>* ad = AdaptAssignableDataSource<T>()( target );
            typename AssignableDataSource<T>::shared_ptr ad = AssignableDataSource<T>::narrow( target.get() );
            const CORBA::Any* any = static_cast<const CORBA::Any*>(blob);
            if ( ad ) {
                PropertyType value;
                if (AnyConversion<PropertyType>::update(*any, value ) ) {
                    ad->set( value );
                    return true;
                }
            }
            return false;
          }

          /**
           * Create a DataSource which is a proxy for a remote object.
           */
          virtual DataSourceBase* proxy( void* data ) const 
          {
            DataSourceBase* result = 0;
            Corba::Expression_ptr e = static_cast<Corba::Expression_ptr>(data);

            // first try as assignable DS, if not possible, try as normal DS.
            result = Corba::ExpressionProxy::NarrowAssignableDataSource<PropertyType>( e );
            if (!result )
                result = Corba::ExpressionProxy::NarrowDataSource<PropertyType>( e );

            return result;
          }

          virtual void* server(DataSourceBase::shared_ptr source, bool assignable, void* arg ) const 
          {
              PortableServer::POA_ptr p = static_cast<PortableServer::POA_ptr>(arg);
              if (assignable){
                  return static_cast<Expression_ptr>(Corba::ExpressionServer::CreateAssignableExpression( source, p ));
                  
              } else {
                  return Corba::ExpressionServer::CreateExpression( source, p );
              }
          }

          virtual void* method(DataSourceBase::shared_ptr source, MethodC* orig, void* arg) const 
          {
              PortableServer::POA_ptr p = static_cast<PortableServer::POA_ptr>(arg);
              return Corba::ExpressionServer::CreateMethod( source, orig, p );
          }

          virtual DataSourceBase* narrowDataSource(DataSourceBase* dsb)
          {
              // then try to see if it is a CORBA object.
              //Corba::ExpressionProxyInterface* prox = dynamic_cast< Corba::ExpressionProxyInterface* >(dsb);
              if ( dsb->serverProtocol() == ORO_CORBA_PROTOCOL_ID ) {
                  Logger::log() << Logger::Debug << "Trying to narrow server "<<dsb->getType()<<" to local "<<DataSource<T>::GetType() <<Logger::endl;
                  Corba::Expression_var expr = (Corba::Expression_ptr)dsb->server(ORO_CORBA_PROTOCOL_ID, 0) ;
                  return Corba::ExpressionProxy::NarrowDataSource<T>( expr.in() );
              }
              // See if the DS contains an Any.
              DataSource<CORBA::Any_var>* aret = dynamic_cast< DataSource<CORBA::Any_var>* >( dsb );
              if (aret){
                  return Corba::ExpressionProxy::NarrowConstant<T>( aret->get().in() );
              }
              return 0;
          }
          
          virtual DataSourceBase* narrowAssignableDataSource(DataSourceBase* dsb)
          {
              // then try to see if it is a CORBA object.
              //Corba::ExpressionProxyInterface* prox = dynamic_cast< Corba::ExpressionProxyInterface* >(dsb);
              if ( dsb->serverProtocol() == ( ORO_CORBA_PROTOCOL_ID ) ) {
                  Corba::Expression_var expr = (Corba::Expression_ptr)dsb->server(ORO_CORBA_PROTOCOL_ID,0) ;
                  return Corba::ExpressionProxy::NarrowAssignableDataSource<T>( expr.in() );
              }
              return 0;
          }

          virtual DataSourceBase* dataProxy( PortInterface* data ) const
          {
              // Detect corba connection
              Corba::CorbaPort* cp = dynamic_cast<Corba::CorbaPort*>( data );
              
              assert(cp);

              return new Corba::CorbaDataObjectProxy<T>("CorbaProxy", cp->getDataChannel());
          }
          
          virtual void* dataServer( DataSourceBase::shared_ptr source, void* arg) const 
          {
              // create a default channel.
              log(Debug) << "Returning Corba Data Object." << endlog();
              return this->server(source, true, arg );
          }

          /**
           * Returns a new BufferInterface<T> object mirroring a remote buffer object server.
           * Used to setup a Corba Data Flow.
           */
          virtual BufferBase* bufferProxy( PortInterface* data ) const 
          {
              // Detect corba connection
              Corba::CorbaPort* cp = dynamic_cast<Corba::CorbaPort*>( data );
              
              assert( cp );

              return new Corba::CorbaBufferProxy<T>( cp->getBufferChannel() );
          }

            virtual void* bufferServer( BufferBase::shared_ptr source, void* arg) const 
          {
              // arg is POA !
              typename RTT::BufferInterface<T>::shared_ptr bi = boost::dynamic_pointer_cast< RTT::BufferInterface<T> >( source );
              log(Debug) << "Creating Corba BufferChannel." << endlog();
              RTT_Corba_BufferChannel_i<T>* cbuf = new RTT_Corba_BufferChannel_i<T>( bi );
              // activate servant:
              CORBA::Object_var ret = cbuf->_this();
              return ret._retn();
          }
      };
}
}

#endif