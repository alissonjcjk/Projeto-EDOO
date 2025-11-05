import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom'
import Layout from './components/Layout.tsx'
import Agendamentos from './pages/Agendamentos'
import Funcionarios from './pages/Funcionarios'
import Clientes from './pages/Clientes'
import Servicos from './pages/Servicos'


const App = () => (
  <BrowserRouter>
    <Layout>
      <Routes>
        <Route path="/" element={<Navigate to="/agendamentos" replace />} />
        <Route
         path="/agendamentos" 
         element={<Agendamentos />
         } 
      />
        <Route 
        path="/funcionarios" 
        element={<Funcionarios />
        } 
      />
          <Route 
          path="/servicos"
          element={<Servicos />}
        />
        <Route 
        path="/clientes" 
        element={<Clientes />
        } 
      />
      </Routes>
    </Layout>
  </BrowserRouter>
)

export default App
