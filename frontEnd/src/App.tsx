import { Routes, Route, Link } from "react-router-dom";
import Agendamentos from "./pages/Agendamentos";
import Funcionarios from "./pages/Funcionarios";
import Clientes from "./pages/Clientes";

export default function App() {
  return (
    <div className="min-h-screen bg-gray-100">
      {/* Navbar */}
      <nav className="bg-white shadow-md py-4 px-8 flex justify-between items-center">
        <h1 className="text-2xl font-bold text-gray-800">Barbearia Manager</h1>
        <div className="space-x-6">
          <Link to="/agendamentos" className="text-gray-700 hover:text-blue-500 font-medium">
            Agendamentos
          </Link>
          <Link to="/funcionarios" className="text-gray-700 hover:text-blue-500 font-medium">
            Funcionários
          </Link>
          <Link to="/clientes" className="text-gray-700 hover:text-blue-500 font-medium">
            Clientes
          </Link>
        </div>
      </nav>

      {/* Conteúdo principal */}
      <div className="p-8">
        <Routes>
          <Route path="/" element={<Agendamentos />} />
          <Route path="/agendamentos" element={<Agendamentos />} />
          <Route path="/funcionarios" element={<Funcionarios />} />
          <Route path="/clientes" element={<Clientes />} />
        </Routes>
      </div>
    </div>
  );
}
