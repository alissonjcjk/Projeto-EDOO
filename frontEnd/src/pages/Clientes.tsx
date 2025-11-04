import { useState } from 'react'
import Modal from '../components/modal/Modal'
import ClienteForm from '../components/modal/ClienteForm'

interface Cliente {
  id: number;
  nome: string;
  email: string;
  contato: string;
  servicoPreferido: string;
}

export default function ClientesPage() {
  const [open, setOpen] = useState(false)
  const [clientes, setClientes] = useState<Cliente[]>([
    {
      id: 1,
      nome: 'José Guiberna',
      email: 'jpz@chu.qlc.br',
      contato: '(11) 99998-1019',
      servicoPreferido: 'Corte Social'
    },
    {
      id: 2,
      nome: 'José Guiberna',
      email: 'jpz@chu.qlc.br',
      contato: '(11) 99998-1019',
      servicoPreferido: 'Corte Social'
    },
    {
      id: 3,
      nome: 'José Guiberna',
      email: 'jpz@chu.qlc.br',
      contato: '(11) 99998-1019',
      servicoPreferido: 'Corte Social'
    }
  ]);

  const handleEditar = (id: number) => {
    console.log('Editar cliente:', id);
    // Aqui você integrará com o backend
  };

  const handleExcluir = (id: number) => {
    setClientes(clientes.filter(cliente => cliente.id !== id));
    // Aqui você integrará com o backend
  };

  return (
    <div className="p-6">
      <div className="mb-8 flex items-center justify-between">
        <div>
          <h1 className="text-3xl font-semibold mb-2">Clientes</h1>
          <p className="text-xl text-gray-600">Gerencie a base de clientes da barbearia</p>
        </div>
        <div>
          <button onClick={() => setOpen(true)} className="bg-red-600 text-white px-6 py-2 rounded-lg hover:bg-red-700 transition duration-200 font-semibold" aria-label="Novo Cliente">+ Novo Cliente</button>
        </div>
      </div>

      <div className="bg-white rounded-lg border border-gray-200 overflow-hidden">
        <div className="overflow-x-auto">
          <table className="min-w-full divide-y divide-gray-200">
            <thead className="bg-gray-50">
              <tr>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Nome</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Email</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Contato</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Serviço Preferido</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Ações</th>
              </tr>
            </thead>
            <tbody className="bg-white divide-y divide-gray-200">
              {clientes.map((cliente) => (
                <tr key={cliente.id} className="hover:bg-gray-50 transition-colors">
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm font-medium text-gray-900">{cliente.nome}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{cliente.email}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{cliente.contato}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{cliente.servicoPreferido}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap text-sm font-medium">
                    <button 
                      onClick={() => handleEditar(cliente.id)}
                      className="text-blue-600 hover:text-blue-900 mr-4 font-semibold"
                    >
                      Editar
                    </button>
                    <button 
                      onClick={() => handleExcluir(cliente.id)}
                      className="text-red-600 hover:text-red-900 font-semibold"
                    >
                      Excluir
                    </button>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>

        
      </div>
      
      <Modal isOpen={open} onClose={() => setOpen(false)} title="Novo Cliente">
				<ClienteForm onCancel={() => setOpen(false)} onSave={() => setOpen(false)} />
			</Modal>

			{/* conteúdo da página vai aqui */}
    </div>
  );
}